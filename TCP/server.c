/*	TCP Client
	E/16/267
	Parackrama G.T.W
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char**argv)
{
	int listenfd,connfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;
	//size of the file is response for a client's 'request'
	char* fileSize = "10000"; 
	char buffer[1000];
	

	// one socket is dedicated to listening 
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	
	/* initialize a sockaddr_in struct with our own address information for
	binding the socket */
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(32000);
	
	/* binding */
	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	listen(listenfd,0);
	clilen=sizeof(cliaddr);
	
	FILE *fp;
	
	//open the file for reading
	fp = fopen("source/serverfile.txt", "r");
	
	//handeling if file does not exist 
	if (fp == NULL) {
        char* error_msg = "error opening file.\n";
        printf("%s", error_msg);
    }
	
	/* accept the client with a different socket. */
	connfd = accept(listenfd,(struct sockaddr *) &cliaddr, &clilen); // the uninitialized cliaddr variable is filled in with the
	n = recvfrom(connfd,buffer,1000,0,(struct sockaddr *)&cliaddr,&clilen);//information of the client by recvfrom function
	buffer[n] = 0;
	sendto(connfd,fileSize,strlen(fileSize),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));//send the file size
	printf("Received:%s\n",buffer);
	
	//read the file and send it
    while (fgets(buffer, 1000, (FILE*)fp) != NULL){
    	sendto(connfd,buffer,strlen(buffer),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
    	//printf("%s\n",buffer);
    }
   
   
   fclose(fp);//close the file
   
	return 0;
}
