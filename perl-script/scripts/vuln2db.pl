#! /usr/bin/perl -w
#
#  Extract vulnerability records detailed in NIST NVD XML files. Save the
#  records into a database.

use strict;
use warnings;

use FindBin;
use lib qq($FindBin::Bin/../lib);

use NVD;
use Dumpvalue;

if (@ARGV < 1) {
    die "Extract NVD vulnerability records into a SQLite database file\n",
        "Usage:\n    $0 <NVD_XML_files>\n\n Please pass in a valid xml file to start!";
}


my $log_postfix = "_log.txt";
foreach my $xml_file (@ARGV) {	
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
			# save the parsed data to the database
			NVD::save2db(\%vuln);
		}
	}
	print "-----------------------------------------------------------------------\n\n\n\n\n";
}