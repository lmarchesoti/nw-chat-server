#ifndef _CONNECTION_POOL_H_
#define _CONNECTION_POOL_H_

#include <string>
#include <memory>
#include <map>
#include <mutex>
#include <condition_variable>
#include <thread>

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
	void broadcast(std::string, std::string);
	void send_to_user(std::string, std::string);

private:

  bool validate_username(std::shared_ptr<Connection>);
	void send_user_list(std::string);
	void route();

  std::recursive_mutex pool_recursive_mutex;
  std::map<std::string, std::shared_ptr<Connection>> pool;
  std::shared_ptr<MsgQueue> msg_q;
	std::condition_variable_any msg_q_cv;
	std::thread router;
};

#endif
