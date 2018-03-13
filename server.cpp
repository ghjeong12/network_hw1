#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

using namespace std;

int main()
{
    char recvline[100];
    char sendline[100];
    int listen_fd, comm_fd;

    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    //bzero( &servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(30000);

    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listen_fd, 10);

    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
  
    fd_set readset;
    int state;
    while(1)
    { 
      FD_ZERO (&readset);
      FD_SET(0, &readset);
      FD_SET(comm_fd, &readset);
      state = select(comm_fd+1, &readset, 0, 0, 0);

      memset(sendline, 0, sizeof(sendline));
      memset(recvline, 0, sizeof(recvline));
	    //bzero( str, 100);
	    //bzero(sendline, 100);
      if(state < 0)
      {
        cout <<"[ERROR]" << endl;
        break;
      }
      else
      {
        if(FD_ISSET(comm_fd, &readset))
        {
	        read(comm_fd, recvline, sizeof(recvline));

	        //printf("[Client] %s", recvline);
          cout << "[Client] " << recvline << endl;
        }
        if(FD_ISSET(0, &readset))
        {
	        string s;
          getline(cin,s);
          //fgets(sendline, 100, stdin);
          //printf("Server : %s", sendline);
	        write(comm_fd, s.c_str(), s.length());
          //write(comm_fd, sendline, strlen(sendline)+1);
        }
      }
    }
    close(comm_fd);
}
