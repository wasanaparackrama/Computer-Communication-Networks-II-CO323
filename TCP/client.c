/*	TCP Client
	E/16/267
	Parackrama G.T.W
*/



#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr;
	char banner[] = "request";
	char buffer[1000];
	int size,i;
	int file_state=0;
	
	
	if (argc != 2)
	{
	printf("usage: ./%s <IP address>\n",argv[0]);
	return -1;
	}
	
	//create socket to connect 
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	//IP address information of the server to connect to 
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);;
	servaddr.sin_port=htons(32000);
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	//send the request string
	sendto(sockfd,banner,strlen(banner),0, (struct sockaddr*)&servaddr,sizeof(servaddr)); 
	//getting the file size
	n=recvfrom(sockfd,buffer,1000,0,NULL,NULL);
	buffer[n]=0;
    sscanf(buffer, "%d", &size); 
	printf("Received:%d\n",size);

	FILE *file;
	//open the file for append
    file = fopen("serverfile.txt", "a");

	//check whether the size of the file is round filesize or not
	int filesize;
	if(size/1000.0 >size/1000){
		filesize = (size/1000) +1;
	}else{
		filesize = (size/1000);
	}
	
	// receive the file content and append it to file
	for(i=0;i<filesize;i++){
		char buff[1000];
		n=recvfrom(sockfd,buffer,1000,0,NULL,NULL);
		buffer[n]=0;	
		
		//write content to file
	    fprintf(file,"%s", buffer);
	    file_state=1;
	}
	
	if(file_state==1){
		printf("file successfully received\n");
	}
	//close the file
	fclose(file);
		
		
	
	return 0;
}
