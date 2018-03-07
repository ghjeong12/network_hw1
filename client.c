#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>

int main(int argc,char **argv)
{
    int sockfd, n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;

    /* Setup Socketes Configuration*/
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);

    servaddr.sin_family=AF_INET;
    /* Use port 30000 */
    servaddr.sin_port=htons(30000);

    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));

    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    while(1)
    {
      bzero( sendline, 100);
      bzero( recvline, 100);
      printf(">> ");
      fgets(sendline,100,stdin); /*stdin = 0 , for standard input */
      //printf("[Client] %s", sendline);

	    write(sockfd,sendline,strlen(sendline)+1);
	    read(sockfd,recvline,100);
	    printf("[Server] %s",recvline);
    }

}
