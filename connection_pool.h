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

private:

  bool validate_username(std::shared_ptr<Connection>);

  std::mutex pool_mutex;
  std::map<std::string, std::shared_ptr<Connection>> pool;
  std::shared_ptr<MsgQueue> msg_q;
};

#endif
