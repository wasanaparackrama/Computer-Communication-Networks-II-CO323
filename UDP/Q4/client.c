/* 	Ex4 - Time client
	E/16/267 
	Parackrama G.T.W*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char** argv){
	int sockfd,n;
	struct sockaddr_in serverAddr;
	char* sendLine="Hello UDP server! This is UDP client. Send time!";
	char receiveLine[1000];
	
	if(argc!=2){
		printf("usage: %s <IP address>\n",argv[0] );
		return -1;
	}
	//creat socket
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&serverAddr,sizeof(serverAddr));
	
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=inet_addr(argv[1]);
	serverAddr.sin_port=htons(32000);
	
	sendto(sockfd,sendLine,strlen(sendLine),0,(struct sockaddr*)&serverAddr,sizeof(serverAddr));

	while(1){
		n=recvfrom(sockfd,receiveLine,1000,0,NULL,NULL);
		receiveLine[n]=0;
		printf("Received: %s\n", receiveLine);
	}
	return 0;
}