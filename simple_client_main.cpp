#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, char** argv )
{
  try {
    ClientSocket client_socket ( "localhost", 30000 );
    std::string reply;

    try{
	    while(1)
      {
        std::string input_text;
	      //std::cin >> input_text;
        std::cout<<">> ";
        std::getline (std::cin,input_text);
        client_socket << input_text;
	      //client_socket << "Test message.";
        client_socket >> reply;
        std::cout << ">> [Server] " << reply << std::endl;
      }
    }
    catch ( SocketException& ) {}

    //std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

  }
  catch ( SocketException& e )  {
    std::cout << "Exception was caught:" << e.description() << "\n";
  }

  return 0;
}
