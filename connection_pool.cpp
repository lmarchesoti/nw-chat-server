#include "connection_pool.h"

void ConnectionPool::add(std::string name, std::shared_ptr<Connection> conn){

  pool[name] = conn;
}

void ConnectionPool::remove(std::string name){

  pool.at(name) = nullptr;
}

std::shared_ptr<Connection> ConnectionPool::operator[](std::string name) {

  return pool.at(name);
}

