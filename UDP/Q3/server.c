/* 	Ex-3 UDP SCP server
	
	E/16/267 
	Parackrama G.T.W
	
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char**argv){
	int sockfd,n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];
	
	//create a socket
	sockfd=socket(AF_INET,SOCK_DGRAM,0);	
	//address family	
	servaddr.sin_family = AF_INET;
	//IP address in the network byte order
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);	
	//assign port
	servaddr.sin_port=htons(32000);
	
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	len = sizeof(cliaddr);

	n=recvfrom(sockfd,mesg,1000,0,(struct sockaddr*)&cliaddr,&len);	
	sendto(sockfd,"ack",3,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	mesg[n] = 0;
	printf("Received: %s\n",mesg);
	printf("Sent : ack\n\n");
	int  no_Lines = atoi(mesg);
	
	
	int i;
	for(i=0;i< no_Lines;i++)
	{
		n=recvfrom(sockfd,mesg,1000,0,(struct sockaddr*)&cliaddr,&len);	
		int j;
		char newmesg[n];
		for(j=0;j<n;j++)
		{
			newmesg[j] = toupper(mesg[j]);	
		}

		sendto(sockfd,newmesg,n,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
		mesg[n] = 0;
		printf("Received: %s",mesg);
		printf("Sent : %s\n",mesg);	
	}
	
	return 0;
}