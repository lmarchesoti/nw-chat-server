/*
** server.cpp
*/

#include "acceptor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include <string>

class Connection {

public:
  Connection(int sock) : sockfd(sock) { };
  ~Connection();
  void send_msg(std::string);

private:
  int sockfd;

};

Connection::~Connection(){

  close(sockfd);

}

void Connection::send_msg(std::string msg){

  if (send(sockfd, msg.c_str(), msg.length(), 0) == -1)
      perror("send");

}

int main(void)
{

    int new_fd;

    Acceptor acceptor;
    acceptor.setup();

    while(1) {  // main accept() loop
	//new_fd = acceptor.listen_accept();
	Connection conn(acceptor.listen_accept());
	conn.send_msg("Hello, world!");

	//close(new_fd);
	exit(0);
    }

    return 0;
}
