#include "connection.h"
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "connection_pool.h"

#define MAXDATASIZE 100 // max number of bytes we can get at once

Connection::~Connection(){

	//this->listener.join();
  close(*sockfd);

}

void Connection::send_msg(std::string msg){

  if (send(*sockfd, msg.c_str(), msg.length(), 0) == -1)
      perror("send");

}

std::string Connection::receive() {

  char buf[MAXDATASIZE];
  int numbytes;  

  if ((numbytes = recv(*sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
      perror("recv");
		std::cerr << this->username + " disconnected." << std::endl;
      //exit(1);
		throw false;
  }

  buf[numbytes] = '\0';

  return std::string(buf);
}

void Connection::disconnect(){

  shutdown(*sockfd, SHUT_RDWR);
}

void Connection::start_listening() {

	this->active = true;
	this->conn_pool->broadcast(this->username, username + " connected.");
	this->listener = std::thread(&Connection::listen, std::ref(*this));
	this->listener.detach();
}

void Connection::listen() {

	std::string msg;

	try {
		while (this->active) {
			msg = this->receive();
			this->process_data(msg);
		}

	} catch (bool e) {

		this->process_disconnect();
	}
}

void Connection::process_data(std::string msg) {

	std::string command;

	this->msg_buffer += msg;
	
	this->strip_leading_linebreaks();

	// if there is enough of a command
	int first_terminator_pos = this->msg_buffer.find('\n');
	if(this->msg_buffer.size() > 0 &&
		 first_terminator_pos != std::string::npos) {

		// extract command
		std::string command = msg_buffer.substr(0, first_terminator_pos);

		if (command == "disconnect") {
			this->process_disconnect();
		}

		if (command == "message") {

			// TODO
		}
	}
}

void Connection::strip_leading_linebreaks() {

	if(this->msg_buffer.size() > 0){

		while(this->msg_buffer.front() == '\n')
			this->msg_buffer.erase(0, 1);
	}
}
void Connection::process_disconnect() {

	this->active = false;
	std::cerr << this->username << " disconnected" << std::endl;
	this->conn_pool->broadcast(this->username, username + " disconnected.");
	this->conn_pool->remove(this->username);
}

void Connection::process_message(std::string to) {

}
