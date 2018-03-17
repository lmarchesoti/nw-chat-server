#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <string>

class Connection {

public:
  Connection() : sockfd(0) { };
  Connection(int sock) : sockfd(sock) { };
  ~Connection();
  void send_msg(std::string);

private:
  int sockfd;

};

#endif
