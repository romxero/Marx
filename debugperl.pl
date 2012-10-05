#~ #!/usr/bin/perl
#~ 
#~ use strict;
#~ use Socket;
#~ $| = 1;
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
#~ #socket settings
#~ my $host = $ARGV[0];
#~ 
#~ my $directive = $ARGV[1];
#~ my $priority = $ARGV[2];
#~ chomp($host);
#~ my $recieve = $ZERO_OUT_VALUE;

#!/usr/bin/perl -w
# client.pl
#----------------

use strict;
use Socket;

# initialize host and port
my $host = 'localhost';
my $port = 65000;
my $server = "localhost";
my $recieveVar = ''; 

        socket(my $socket, PF_INET, SOCK_STREAM, 0)
            or die "socket: $!";


        connect($socket, pack_sockaddr_in($port, inet_aton($server)))
            or die "connect: $!";
            binmode($socket);
            syswrite($socket,chr(hex($QUEUE_JOBS)));
            
            
            
            
		#~ chomp($QUEUE_JOBS);
        #~ print $socket chr(hex($QUEUE_JOBS));
        #~ send($socket,$QUEUE_JOBS,0);
        	#  recv(sockfd,recieveVarPtr,sizeof(int),0);
        #~ recv($socket,$recieveVar,1000,0);
        #~ print chr(hex($recieveVar));
        #~ print "HELLO!!";
        #~ while(<$socket>)
        #~ {
			#~ print $_;
		#~ }
        #~ print $socket chr(hex($QUEUE_JOBS));
        #~ print $socket chr(hex($QUEUE_JOBS));
        #~ print $socket chr(hex($QUEUE_JOBS));
        #~ print $socket chr(hex($QUEUE_JOBS));
        #~ print <$socket>;
close($socket);

#~ # create the socket, connect to the port
#~ socket(SOCKET,PF_INET,SOCK_STREAM,(getprotobyname('tcp'))[2])
   #~ or die "Can't create a socket $!\n";
#~ connect( SOCKET, pack( 'Sn4x8', AF_INET, $port, $server ))
       #~ or die "Can't connect to port $port! \n";
#~ 
#~ my $line;
#~ while ($line = <SOCKET>) {
	#~ print "$line\n";
#~ }
#~ close SOCKET or die "close: $!";
