/*
** server.cpp
*/

#include "acceptor.h"
#include "connection.h"
#include "connection_pool.h"

#include <map>
#include <memory>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>



int main(void)
{

  ConnectionPool pool;

  Acceptor acceptor;
  acceptor.setup();

  while(1) {  // main accept() loop

    int sock = acceptor.listen_accept();
    auto conn = std::make_shared<Connection>(sock);

    pool.add("john", conn);
    pool["john"]->send_msg("Hello, world!");
    pool.remove("john");

    exit(0);
  }

  return 0;
}
