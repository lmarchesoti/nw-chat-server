#include "connection_pool.h"
#include "acceptor.h"

#include <sys/types.h>
#include <unistd.h>
#include <chrono>

void ConnectionPool::add(std::string name, std::shared_ptr<Connection> conn){

  pool[name] = conn;
}

void ConnectionPool::remove(std::string name){

  pool.at(name) = nullptr;
}

std::shared_ptr<Connection> ConnectionPool::operator[](std::string name) {

  return pool.at(name);
}

void ConnectionPool::start_listening() {

  if (!fork()){

    Acceptor acceptor;
    acceptor.setup();

    while(true) {  // main accept() loop

      int sock = acceptor.listen_accept();
      auto conn = std::make_shared<Connection>(sock);

      add("john", conn);
      pool["john"]->send_msg("Hello, world!");
      remove("john");

      exit(0);
    }
  }
}

void ConnectionPool::idle() {

  // 60 seconds in microseconds
  int duration = 60*1000*1000;

  while(true)
    usleep(duration);
}
