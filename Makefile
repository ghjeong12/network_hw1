all : server client

server : server.o
	g++ -o server server.o

client : client.o
	g++ -o client client.o

server.o : server.cpp
client.o : client.cpp

clean :
	rm -f *.o server client
