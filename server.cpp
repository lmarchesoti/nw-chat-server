/*
** server.cpp
*/

#include "connection_pool.h"

int main(void)
{

  ConnectionPool pool;

  pool.start_listening();
  pool.idle();

  return 0;
}
