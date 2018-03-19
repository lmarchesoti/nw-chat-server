#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <string>
#include <memory>

#include "msg_queue.h"

class Connection {

public:
  //Connection() : sockfd(0) { };
  Connection(std::shared_ptr<int> sock, std::shared_ptr<MsgQueue> mq) : sockfd(sock), msg_q(mq) { };
  ~Connection();
  void send_msg(std::string);
  std::string receive();
  void disconnect();

private:
  std::shared_ptr<int> sockfd;
	std::shared_ptr<MsgQueue> msg_q;

};

#endif
