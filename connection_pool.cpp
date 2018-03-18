#include "connection_pool.h"
#include "acceptor.h"

#include <sys/types.h>
#include <unistd.h>
#include <chrono>
#include <mutex>

ConnectionPool::ConnectionPool() {
  pool = std::make_shared<std::map<std::string, std::shared_ptr<Connection>>>();
}

//std::mutex pool_mutex;

void ConnectionPool::add(std::string name, std::shared_ptr<Connection> conn){

  //std::lock_guard<std::mutex> lock(pool_mutex);
  (*pool)[name] = conn;
}

void ConnectionPool::remove(std::string name){

  //std::lock_guard<std::mutex> lock(pool_mutex);
  pool->erase(name);
}

std::shared_ptr<Connection> ConnectionPool::operator[](std::string name) {

  //std::lock_guard<std::mutex> lock(pool_mutex);
  return pool->at(name);
}

void ConnectionPool::start_listening() {

  Acceptor acceptor;
  acceptor.setup();

  while(true) {  // main accept() loop

    auto sock = acceptor.listen_accept();
    auto conn = std::make_shared<Connection>(sock);

    std::string username = conn->receive();

    if ((pool->find(username) == pool->end())) {
    //if (pool.count(username) == 0) {

      this->add(username, conn);
      printf("new user %s\n", username.c_str());

      conn->send_msg("OK");
      if(conn->receive() != "OK")
	this->remove(username);

      conn->send_msg("Hello, world!");
      //(*pool)[username]->send_msg("1");
      //(*pool)[username]->send_msg("Hello, world!");
      //remove(username);
    } else {

      printf("denied user %s\n", username.c_str());
      conn->send_msg("0");
    }

  }
}

void ConnectionPool::idle() {

  // 60 seconds in microseconds
  int duration = 60*1000*1000;

  while(true)
    usleep(duration);
}
