#! /usr/bin/perl -w
#
#  Extract vulnerability records detailed in NIST NVD XML files. Save the
#  records into a database.

use strict;
use warnings;

use FindBin;
use lib qq($FindBin::Bin/../lib);

use NVD;
use XML::LibXML;
use Dumpvalue;

# prevent empty xml file pass in
if (@ARGV < 1) {
    die "Extract NVD vulnerability records into a SQLite database file\n",
        "Usage:\n    $0 <NVD_XML_files>\n\n Please pass in a valid xml file to start!";
}


my $log_postfix = "-log.txt";
foreach my $xml_file (@ARGV) {
	my $dumper = Dumpvalue->new;

	# validate the xml file
	my $validate = eval {XML::LibXML->load_xml(location => $xml_file) };

	print "-----------------------------------------------------------------------\n";
	if($@) {
		print "XML file reading error: $xml_file \n\n $@ \nPlease make sure you pass in a valid xml file!\n\n";
	} else {
		print "XML file: $xml_file validated!\n\n";
		my %vuln = NVD::extract($xml_file);
		# prevent case when the returned hash from NVD::extract are empty
		if(%vuln) {
			# define the filename
			my $fileName = substr $xml_file, 9, 11;
			$fileName .= $log_postfix;

			# save the output to a .txt file located in /log folder
			print "The NVD report for: $fileName is: \n\n\n\n\n";
			open(my $fh, ">", "./log/$fileName") or die "$fileName could not be created or opened, $!";
			my $old_fh = select($fh);
			$dumper -> dumpValue(\%vuln);
			close $fh;
			select($old_fh);
			$dumper -> dumpValue(\%vuln);
		}
	}
	print "-----------------------------------------------------------------------\n\n\n\n\n";
}