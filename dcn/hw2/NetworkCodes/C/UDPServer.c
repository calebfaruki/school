#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


void diep(char *s)
{
	perror(s);
	exit(1);
}

int main(void)
{
	const int BUFLEN=512;
	const int NPACK=10;
	const int PORT=7019;

	struct sockaddr_in si_me, si_other;
	int s, i, slen=sizeof(si_other);
   	char buf[BUFLEN];
   
	//create a UDP socket
  	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    		diep("socket");

	//bind  the socket to port number 
    	memset((char *) &si_me, 0, sizeof(si_me));
    	si_me.sin_family = AF_INET;
        si_me.sin_port = htons(PORT);
        si_me.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(s, &si_me, sizeof(si_me))==-1)
    		diep("bind");

	//repeat for 10 times: read from socket and write the received pakcet
	//to terminal
    	for (i=0; i<NPACK; i++) {
    		if (recvfrom(s, buf, BUFLEN, 0, &si_other, &slen)==-1)
    			diep("recvfrom()");
    		printf("Received packet from %s:%d\nData: %s\n\n", 
    			inet_ntoa(si_other.sin_addr), //client's IP
			ntohs(si_other.sin_port),  //client's port #
			buf);

		//Todo: send an echo message to client 
    }
    
   close(s);
   return 0;
}