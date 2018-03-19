#ifndef _MSG_QUEUE_H_
#define _MSG_QUEUE_H_

#include <string>
#include <queue>
#include <mutex>

class MsgQueue {

public:
  void add_message(std::string, std::string);
  std::pair<std::string, std::string> retrieve_one();

private:

  std::queue<std::pair<std::string, std::string>> queue;
  std::mutex global_lock;
};

#endif
