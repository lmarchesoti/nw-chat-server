#include "connection_pool.h"
#include "acceptor.h"
#include "msg_queue.h"

#include <sys/types.h>
#include <unistd.h>
#include <chrono>
#include <mutex>
#include <memory>

#include <iostream>

ConnectionPool::ConnectionPool() {

  this->msg_q = std::make_shared<MsgQueue>();
}

void ConnectionPool::add(std::string name, std::shared_ptr<Connection> conn){

  std::lock_guard<std::mutex> lock(this->pool_mutex);
  pool[name] = conn;
}

void ConnectionPool::remove(std::string name){

  std::lock_guard<std::mutex> lock(this->pool_mutex);
  pool[name]->disconnect();
  pool.erase(name);
}

void ConnectionPool::start_listening() {

  Acceptor acceptor;
  acceptor.setup();

  while(true) {  // main accept() loop

    auto sock = acceptor.listen_accept();
    auto conn = std::make_shared<Connection>(sock);

    std::string username = conn->receive();

    if ((pool.find(username) == pool.end())) {

      if(this->validate_username(conn)) {

	this->add(username, conn);

	printf("new user %s\n", username.c_str());

	// send connection notification
	//this->notify_connect(username);

/*
	conn->send_msg("Hello, world!");
	sleep(1);
	printf("sending goodbye\n");
	conn->send_msg("Goodbye!");

	std::string msg;
	while ((msg = conn->receive()) == "ping");
	std::cout << msg << std::endl;
	//pool[username]->send_msg("1");
	//pool[username]->send_msg("Hello, world!");
	//remove(username);
*/

      } else {

	this->remove(username);
      }

    } else {

      printf("denied user %s\n", username.c_str());
      conn->send_msg("0");
    }

  }
}

void ConnectionPool::idle() {

  int duration = 60;

  while(true)
    sleep(duration);
}

bool ConnectionPool::validate_username(std::shared_ptr<Connection> conn) {

  conn->send_msg("OK");
  if(conn->receive() != "OK")
    return false;

  return true;
}

//void ConnectionPool::notify_connect(std::string username) {

  

//}
