#ifndef _CONNECTION_POOL_H_
#define _CONNECTION_POOL_H_

#include <string>
#include <memory>
#include <map>

#include "connection.h"

class ConnectionPool {

public:
  void add(std::string, std::shared_ptr<Connection>);
  void remove(std::string);
  std::shared_ptr<Connection> operator[](std::string);

private:
  std::map<std::string, std::shared_ptr<Connection>> pool;
};

#endif
