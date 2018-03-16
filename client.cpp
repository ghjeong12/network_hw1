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
  /*
  fd_set writeset;
  FD_ZERO (&writeset);
	FD_SET (0, &writeset);
  FD_SET (sockfd, &writeset);
  */
  while(1)
	{
    fd_set readset;
    FD_ZERO (&readset);
	  FD_SET (0, &readset);
    FD_SET (sockfd, &readset);
    int state = select(sockfd+1, &readset, NULL,NULL,NULL);
    
    memset(sendline, 0, sizeof(sendline));
    memset(recvline, 0, sizeof(recvline));
    //bzero( sendline, 100);
		//bzero( recvline, 100);
		if(state < 0)
    {
      cout << "[ERROR]" << endl;
      break;
    }
    else
    {
      if(FD_ISSET(0, &readset))
      {
        string s;
        getline(std::cin, s); 
		    write(sockfd,s.c_str(),s.length());
      }
      if(FD_ISSET(sockfd, &readset))
      {
        int read_rtn = read(sockfd,recvline,sizeof(recvline));
        if(read_rtn > 0)
        {
          cout << "[Server User] " << recvline << endl;
        }
      }
		//printf("[Server] %s",recvline);
    }
  }

}
