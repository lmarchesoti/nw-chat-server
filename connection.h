#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <string>
#include <memory>
#include <thread>
#include <atomic>

//#include "connection_pool.h"
//#include "msg_queue.h"

class ConnectionPool;

class Connection {

public:
  //Connection() : sockfd(0) { };
  Connection(std::shared_ptr<int> sock, ConnectionPool* cp) : sockfd(sock), conn_pool(cp) { };
  ~Connection();
  void send_msg(std::string);
  std::string receive();
  void disconnect();
	void start_listening();

	std::string username;

private:
	void listen();
	void process_disconnect();
	void process_message(std::string);
	void process_data(std::string);
	void strip_leading_linebreaks();

  std::shared_ptr<int> sockfd;
	//std::shared_ptr<MsgQueue> msg_q;
	std::thread listener;
	ConnectionPool* conn_pool;
	std::string msg_buffer;
	std::atomic<bool> active;

};

#endif
