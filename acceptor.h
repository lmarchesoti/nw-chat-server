#ifndef __ACCEPTOR_H_
#define __ACCEPTOR_H_

#include <memory>

class Acceptor {
public:

  ~Acceptor();
  std::shared_ptr<int> listen_accept();
  void setup();

private:
  int sockfd;

};

#endif
