#include "msg_queue.h"

void MsgQueue::add_message(std::string username, std::string message) {

  std::lock_guard<std::mutex> lock(this->global_lock);
  //queue.push_back(std::pair(username, message));
  this->queue.emplace(username, message);
}

std::pair<std::string, std::string> MsgQueue::retrieve_one() {

  std::lock_guard<std::mutex> lock(this->global_lock);

  auto msg_object = this->queue.front();

  this->queue.pop();
  return msg_object;
}
