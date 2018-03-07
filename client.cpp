#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

using namespace std;

int main(int argc,char **argv)
{
	int sockfd, n;
	char sendline[100];
	char recvline[100];
	struct sockaddr_in servaddr;

	/* Setup Socketes Configuration*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//bzero(&servaddr,sizeof servaddr);
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	/* Use port 30000 */
	servaddr.sin_port=htons(30000);

	inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));

	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	while(1)
	{
        memset(sendline, 0, sizeof(sendline));
        memset(recvline, 0, sizeof(recvline));
        //bzero( sendline, 100);
		//bzero( recvline, 100);
		cout << ">> ";
		fgets(sendline, 100, stdin); /*stdin = 0 , for standard input */
		//printf("[Client] %s", sendline);
		write(sockfd,sendline,strlen(sendline)+1);
		read(sockfd,recvline,100);
        cout << "[Server] " << recvline;
		//printf("[Server] %s",recvline);
	}

}
