#!/usr/bin/perl

use strict;
use warnings;

my $defaultFile = "/dev/shm/joblist.txt";
my $host = "localhost";


open(FILE, ">", $defaultFile);
while (<@ARGV>)
{
	chomp($_);
	
	print FILE $_ . "\n";
	
}
close(FILE); 
system("jobsender $host $defaultFile");

#~ 
#~ qx{jobsender \$host \$defualtFile};
#~ qx{jobsender \$host \$defualtFile};
#~ system("jobsender $host" $defualtFile);
