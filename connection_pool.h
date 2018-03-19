#ifndef _CONNECTION_POOL_H_
#define _CONNECTION_POOL_H_

#include <string>
#include <memory>
#include <map>
#include <mutex>

#include "msg_queue.h"
#include "connection.h"

class ConnectionPool {

public:

  ConnectionPool();
  void add(std::string, std::shared_ptr<Connection>);
  void remove(std::string);
  void start_listening();
  void idle();
	void route_messages();

private:

  bool validate_username(std::shared_ptr<Connection>);
	void send_to_user(std::string, std::string);
	void broadcast_connection(std::string);

  std::mutex pool_mutex;
  std::map<std::string, std::shared_ptr<Connection>> pool;
  std::shared_ptr<MsgQueue> msg_q;
};

#endif
