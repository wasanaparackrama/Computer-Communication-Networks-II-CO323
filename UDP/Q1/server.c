/* 	Ex-1 sample UDP Server
	E/16/267
	Parackrama G.T.W.
	
*/

#include <sys/socket.h> 
#include <netinet/in.h> 
#include <strings.h> 
#include <stdio.h> 
int main(int argc, char**argv) 
{ 
	int sockfd,n; 
	struct sockaddr_in servaddr, cliaddr; 
	socklen_t len; 
	char mesg[1000]; 
	char* banner = "Hello UDP client! This is UDP server"; 

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

	while(1){
		
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len); 
		sendto(sockfd,banner,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)); 
		mesg[n] = 0; 
		printf("Received: %s\n",mesg);
	} 
	return 0; 
}
