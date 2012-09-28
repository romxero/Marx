#!/usr/bin/perl
use IO::Socket;
use strict;
use warnings;
$| = 1;
my $ZERO_OUT_VALUE = 0x0000;

my $SEND_HOSTNAME = 0x0001;
my $SEND_BENCHSCORE = 0x0002;
my $SEND_PRIORITY_NUM = 0x0003;
my $RECIEVED_OK = 0x0004; # //this should be very important
my $KILL_PEER = 0x0005;

my $QUEUE_JOBS = 0x0006;
my $SEND_DIRECTIVE = 0x0007;
my $ROUND_ROBIN = 0x0008;
my $SPECIFIC_PEERS = 0x0009;
my $MIN = 0x000A;

my $MAX = 0x000B;
my $QUEUE_JOBS_END = 0x000C;

my $SEND_JOB = 0x000D;
my $SEND_JOB_UNAME = 0x000E;
my $JOB_RECIEVED_OK = 0x000F;

my $JOB_RECIEVED_ERROR = 0x0010;
my $KILL_SERVER = 0x0011;
my $READY_FOR_JOBS = 0x0012;

my $RECIEVED_ERROR = 0x0013;
#socket settings
my $host = $ARGV[0];

my $directive = $ARGV[1];
my $priority = $ARGV[2];
chomp($host);
my $recieve = $ZERO_OUT_VALUE;

my $socket = new IO::Socket::INET
	(
	PeerAddr => $host,
	PeerPort => '65000',
    Proto => 'tcp',
    Type => SOCK_STREAM,
	) or die "Could not create socket: $!\n";

my @jobList = @ARGV;

#~ foreach my $item (@ARGV)
#~ {
	#~ chomp($item);
	#~ print $item . "\0" . "\n";
	#~ 
	#~ print $item . "\0";
#~ }

print $socket chr(hex($QUEUE_JOBS));


#~ print hex($recieve) . "\n";
#~ print (<$socket>);
#~ read($socket,$recieve,100);
$socket->recv($recieve,length($ZERO_OUT_VALUE));
print $recieve;
print $socket chr(hex($priority));
$socket->recv($recieve,length($ZERO_OUT_VALUE));
print $socket chr(hex($ROUND_ROBIN));
$socket->recv($recieve,length($ZERO_OUT_VALUE));
if ($recieve eq $SEND_PRIORITY_NUM)
{
	print "YAH!";
}

#~ $recieve = <$socket>;
#~ print $recieve . "\n";
#~ 
#~ if ($recieve eq chr(hex($SEND_PRIORITY_NUM)))
#~ {
	#~ print $socket chr(hex($priority));
#~ }
#~ 
#~ $recieve = <$socket>;
#~ print $recieve . "\n";
#~ if ($recieve == $SEND_DIRECTIVE)
#~ {
	#~ print $socket chr(hex($ROUND_ROBIN));
#~ }
#~ 
#~ $recieve = <$socket>;
#~ print $recieve . "\n";
#~ if ($recieve == $READY_FOR_JOBS)
#~ {
	#~ 
			#~ my $count = @ARGV;
			#~ for (my $i = 3; $i < $count; $i++)
			#~ {
				#~ 
				#~ print $socket $ARGV[$i];
				#~ $recieve = <$socket>;
				#~ print $recieve . "\n";
				#~ if ($recieve == $RECIEVED_OK)
				#~ {
					#~ continue;
				#~ }
				#~ else
				#~ {
					#~ 
					#~ last; #breaks out of the loop
				#~ }
				#~ 
			#~ }
				#~ print $socket chr(hex($QUEUE_JOBS_END));	
	#~ 
#~ }
close($socket);

