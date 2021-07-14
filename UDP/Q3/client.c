/* 	Ex-3 UDP SCP client
    E/16/267 
	Parackrama G.T.W
	
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc,char** argv){
	int sockfd,n;
	struct sockaddr_in servaddr;
	char* sendLine="Hello UDP Server! This is a client";
	char receiveLine[1000];
	
	if(argc!=3){
		printf("usage: %s <IP address> <Number of lines>\n",argv[0] );
		return -1;
	}
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(32000);
	
	sendto(sockfd,argv[2],strlen(sendLine),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
	n=recvfrom(sockfd,receiveLine,1000,0,NULL,NULL);
	receiveLine[n]=0;
	printf("Received: %s\n", receiveLine);	
	int i;
	char* input;size_t len = 0;
	int j=atoi(argv[2]);

	for(i=0;i<j;i++){
		
		getline(&input, &len, stdin);
		
		sendto(sockfd,input,strlen(sendLine),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
		n=recvfrom(sockfd,receiveLine,1000,0,NULL,NULL);
		receiveLine[n]=0;
		printf("Received: %s", receiveLine);
	}
	return 0;
}