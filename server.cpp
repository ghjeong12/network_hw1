#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
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
    int num_clients = 10;
    int sock_list[100];
  
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    
    //int comm_fd_2 = accept(listen_fd, (struct sockaddr*) NULL, &tv);
    while(1)
    { 
      FD_ZERO (&readset);
      FD_SET(0, &readset);
      FD_SET(comm_fd, &readset);
      
      /*
      for(int i =0;i<num_clients;i++)
      {
        //comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
      //  cout << "--- " << comm_fd << endl;
      }*/

      state = select(comm_fd+1, &readset, 0, 0, 0);

      memset(sendline, 0, sizeof(sendline));
      memset(recvline, 0, sizeof(recvline));
      if(state < 0)
      {
        cout <<"[ERROR]" << endl;
        break;
      }
      else
      {
        if(FD_ISSET(comm_fd, &readset))
        {
	        int read_rtn = read(comm_fd, recvline, sizeof(recvline));
          
	        //printf("[Client] %s", recvline);
          if(read_rtn > 0)
          {
            if((read_rtn == 1) && (recvline[0] == '1') )
            {
              cout << "1" << endl;
              /*
              string msg = "This client is connected to the server with id " + to_string(comm_fd);

              cout << msg << endl;
              write(comm_fd, msg.c_str(), msg.length()); 
              cout << "Connected Clients : " << num_clients << endl;
              for(int  i = 0; i < num_clients; i++)
              {
                ;
              }*/
            }
            else
              cout << "[Client User] " << recvline << endl;
          }
        }
        
        /* If a server user types something through */
        if(FD_ISSET(0, &readset))  
        {
	        string s;
          getline(cin,s);
	        write(comm_fd, s.c_str(), s.length());
        }
      }
    }
    close(comm_fd);
}
