#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <string>
#include <memory>

class Connection {

public:
  //Connection() : sockfd(0) { };
  Connection(std::shared_ptr<int> sock) : sockfd(sock) { };
  ~Connection();
  void send_msg(std::string);
  std::string receive();
  void disconnect();

private:
  std::shared_ptr<int> sockfd;

};

#endif
