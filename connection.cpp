#include "connection.h"
#include <string>
#include <sys/socket.h>
#include <unistd.h>

Connection::~Connection(){

  close(sockfd);

}

void Connection::send_msg(std::string msg){

  if (send(sockfd, msg.c_str(), msg.length(), 0) == -1)
      perror("send");

}
