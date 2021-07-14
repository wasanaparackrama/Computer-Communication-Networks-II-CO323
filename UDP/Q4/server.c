/* 	Ex4 - Time Server
	E/16/267 
	Parackrama G.T.W
	
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



int main(int argc,char **argv){
	int sockfd,n=10,m;
	struct sockaddr_in serverAddr,clientAddr;
	socklen_t len;
	char message[1000];
	
	char* banner = "Hello UDP client! Now I'm going to send time.";
	int size_banner = strlen(banner);
	
	time_t current_time;
	struct tm * time_info;
	char previous_str[8];
	char time_str[8];
	
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddr.sin_port=htons(32000);
	bind(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));	
	
	len=sizeof(clientAddr);
	m=recvfrom(sockfd,message,1000,0,(struct sockaddr*)&clientAddr,&len);
    sendto(sockfd,banner,size_banner,0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
	message[m] = 0;
	printf("Received: %s\n",message);

	while(1){
		//creat time
		strcpy(previous_str,time_str);
		time(&current_time);
		time_info = localtime(&current_time);
		//getting time
		strftime(time_str, 9, "%H:%M:%S", time_info);
		
		if(previous_str[7]!=time_str[7]){
			sendto(sockfd,time_str,n,0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));		
			printf("Sent : %s\n",time_str);	
		}
		
	}

	return 0;
}