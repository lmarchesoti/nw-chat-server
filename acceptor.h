#ifndef __ACCEPTOR_H_
#define __ACCEPTOR_H_

class Acceptor {
public:

  ~Acceptor();
  int listen_accept();
  void setup();

private:
  int sockfd;

};

#endif
