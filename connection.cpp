#include "connection.h"
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define MAXDATASIZE 100 // max number of bytes we can get at once

Connection::~Connection(){

  close(*sockfd);

}

void Connection::send_msg(std::string msg){

  if (send(*sockfd, msg.c_str(), msg.length(), 0) == -1)
      perror("send");

}

std::string Connection::receive() {

  char buf[MAXDATASIZE];
  int numbytes;  

  if ((numbytes = recv(*sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
      perror("recv");
      exit(1);
  }

  buf[numbytes] = '\0';

  return std::string(buf);
}

void Connection::disconnect(){

  shutdown(*sockfd, SHUT_RDWR);
}

void Connection::start_listening() {

	listener = std::thread(&Connection::listen, std::ref(*this));
}

void Connection::listen() {

	std::string msg;

	while ((msg = this->receive()) == "ping");
	std::cout << msg << std::endl;
}
