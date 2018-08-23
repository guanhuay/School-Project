package NVD;

#  Extract vulnerability records from the XML files provided by NIST in their
#  public data feed at: https://nvd.nist.gov/download.cfm
#
#  This module supports only the NVD XML version 1.2.1 schema. The version 2.0
#  schema is not supported.

use strict;
use warnings;

use XML::LibXML;
use XML::DOM;
use DBI;
use Scalar::Util qw/reftype/;

sub extract {
    my $fname = shift
        or warn("please provide the XML file to load\n"),
        return;

    my %vuln;

    # validate the xml file
    my $validate = eval {XML::LibXML->load_xml(location => $fname) };

    if($@) {
        return;
    } else {
        my $xml = XML::LibXML->load_xml(location => $fname);
        my( $nvd ) = $xml->nonBlankChildNodes;

        for my $entry ($nvd->nonBlankChildNodes) {
            my %value;
            # %value = parse_nvd_entry($entry);
            
            for my $attr ($entry->attributes) {
                my $key = $attr->nodeName;
                my $values = $attr->nodeValue;
                $value{$key} = $values
            }

            # rename 'name' to 'cve_id'
            my $id = $value{cve_id} = delete $value{name};
            $vuln{$id} = \%value;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
        }
    }

    return %vuln;
}

sub save2db {
    my %vuln = %{$_[0]};

    # connect to the database "nvd.db"
    my $driver   = "SQLite";
    my $database = "nvd.db";
    my $dsn = "DBI:$driver:dbname=$database";
    my $userid = "";
    my $password = "";
    my $dbh = DBI->connect($dsn, $userid, $password, { RaiseError => 1 })
                  or die $DBI::errstr;
    print "Opened database successfully\n";

    # define the first table
    my $query = qq(
        CREATE TABLE IF NOT EXISTS first(
            cve_id         TEXT PRIMARY KEY NOT NULL,
            severity       TEXT,
            published      TEXT,
            modified       TEXT););

    # create the first table inside the nvd database
    my $rv = $dbh->do($query) or die $DBI::errstr;

    $query = qq(
        CREATE TABLE IF NOT EXISTS second(
            id             INTEGER PRIMARY KEY AUTOINCREMENT,
            cve_id         TEXT NOT NULL,
            name           TEXT,
            vendor         TEXT););

    # create the second table inside the nvd database
    $rv = $dbh->do($query) or die $DBI::errstr;

    foreach my $values (values %vuln) {
        my %entry = %$values;
        my $cve_id = $entry{'cve_id'};
        my $severity = $entry{'severity'};
        my $published = $entry{'published'};
        my $modified = $entry{'modified'};

        $query = qq(
            INSERT INTO first(cve_id, severity, published, modified)
            VALUES("$cve_id", "$severity", "$published", "$modified"););

        $rv = $dbh->do($query) or die $DBI::errstr;
        print "Records created successfully\n";
    }

    # step 1: store all the vuln_soft->prod hash to array1 and store all cve_id to array2
    my @array1;
    my @array2;
    foreach my $keys (keys %vuln) {
        my $prod = $vuln{$keys}{'vuln_soft'}{'prod'};
        my $cve_id = $vuln{$keys}{'cve_id'};
        push(@array1, $prod);
        push(@array2, $cve_id);        
    }

    # step 2: depend on the type of current element in array, retrieve the name and vendor information and save to the database
    while(@array1){
        my $element = pop(@array1);
        my $cve_id = pop(@array2);
        # case 1: if the current array element is hash
        if(ref $element eq "HASH") {
            my %hash = %$element;
            my $name = $hash{'name'};
            my $vendor = $hash{'vendor'};
            $query = qq(
                INSERT INTO second (cve_id, name, vendor)
                VALUES("$cve_id", "$name", "$vendor"););
            $rv = $dbh->do($query) or die $DBI::errstr;
            print "Records created successfully\n";
        }
        # case 2: if the current array element is array
        if(ref $element eq "ARRAY") {
            my @subarray = @$element;
            foreach my $sub_hash (@subarray) {
                if(ref $sub_hash eq "HASH") {
                    my %sub_hash = %$sub_hash;
                    my $name = $sub_hash{'name'};
                    my $vendor = $sub_hash{'vendor'};
                    $query = qq(
                        INSERT INTO second (cve_id, name, vendor)
                        VALUES("$cve_id", "$name", "$vendor"););
                    $rv = $dbh->do($query) or die $DBI::errstr;
                    print "Records created successfully\n";
                }
            }
        }
    }
}

sub parse_nvd_entry{
    my $entry = shift;

    my %entry;
    for my $node ($entry->nonBlankChildNodes) {
        my $name = $node->nodeName;
        my $value = $node->textContent;
        $value =~ s/^\s+|\s+$//g;

        if ($node->nodeName eq '#text') {
            # The node content is held in an element called: '#text'. This is 
            # returned by the call to the method: textContent. As we recurse 
            # through the document, we rename it to "body".

            $name = "body";
        }

        if ($node->hasChildNodes) {
            # my %value = parse_sub_node($node);
            my %value = parse_nvd_entry($node);
            $value = \%value;
        }

        if (defined $entry{$name}) {
            # This node name is reused within the same parent node
            my $existing_entry = $entry{$name};

            $value = {$name, $value};
            if (ref $existing_entry eq "ARRAY") {
                push @$existing_entry, $value;
            } else {
                $entry{$name} = [$existing_entry, $value];
            }

        } else {
            $entry{$name} = $value;
        }

        if ($node->hasAttributes) {
            my %attr ;
            for my $attr ($node->attributes) {
                $attr{$attr->nodeName} = $attr->nodeValue;
            }

            if (ref $value eq "HASH") {
                @$value{keys %attr} = values %attr;
            } else {
                $entry{$name} = {$name => $value, %attr};
            }
        }
    }

    return %entry;
}

1;
