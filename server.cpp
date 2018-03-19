/*
** server.cpp
*/

#include "connection_pool.h"
#include <thread>

#include <unistd.h>

int main(void)
{

	ConnectionPool pool;

  std::thread t1(&ConnectionPool::start_listening, std::ref(pool));
	pool.route_messages();

  return 0;
}
