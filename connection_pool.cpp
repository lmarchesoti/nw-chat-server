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

  std::lock_guard<std::recursive_mutex> lock(this->pool_recursive_mutex);
  pool[name] = conn;
}

void ConnectionPool::remove(std::string name){

  std::lock_guard<std::recursive_mutex> lock(this->pool_recursive_mutex);
  pool[name]->disconnect();
  pool.erase(name);
}

void ConnectionPool::start_listening() {

  Acceptor acceptor;
  acceptor.setup();

  while(true) {  // main accept() loop

    auto sock = acceptor.listen_accept();
    auto conn = std::make_shared<Connection>(sock, this);

    std::string username = conn->receive();

    if ((pool.find(username) == pool.end())) {

      if(this->validate_username(conn)) {

				conn->username = username;

				printf("new user %s\n", username.c_str());

				this->add(username, conn);

				this->send_user_list(username);

				conn->start_listening();

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

void ConnectionPool::route_messages() {

	while(true) {

		if(this->msg_q->pending()) {
			auto msg_object = this->msg_q->retrieve_one();

			std::string username = msg_object.first;
			std::string msg = msg_object.second;
			this->send_to_user(username, msg);
		}
	}

}

void ConnectionPool::send_to_user(std::string username, std::string msg) {

  std::lock_guard<std::recursive_mutex> lock(this->pool_recursive_mutex);

	try {
		auto conn = this->pool[username];
	//if (conn == nullptr) return;

		conn->send_msg(msg);
	} catch (std::out_of_range e) {

	}
}

void ConnectionPool::broadcast(std::string username, std::string message) {

  std::lock_guard<std::recursive_mutex> lock(this->pool_recursive_mutex);
  
	for(auto it=this->pool.begin(); it!=this->pool.end(); ++it) {

		if (it->first != username) {

			this->msg_q->add_message(it->first, message);
		}
	}
}

void ConnectionPool::send_user_list(std::string username) {

  std::lock_guard<std::recursive_mutex> lock(this->pool_recursive_mutex);
  
	std::string message = "logged users:\n";
	for(auto it=this->pool.begin(); it!=this->pool.end(); ++it) {

		if (it->first != username) {
			message += it->first + "\n";
		}
	}

	this->send_to_user(username, message);
}

