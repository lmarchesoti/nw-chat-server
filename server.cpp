/*
** server.cpp
*/

#include "connection_pool.h"
#include <thread>

int main(void)
{

  ConnectionPool pool;

  std::thread t1(&ConnectionPool::start_listening, std::ref(pool));
  pool.idle();

  return 0;
}
