#include <networking.h>

#include <stdio.h>

typedef struct Connection {} Connection;

Connection *wait_for_connection(int port)
{
  printf("TODO: Implement wait_for_connection");
  return NULL;
}

const char *wait_for_data(Connection *this, int buffer_size)
{
  printf("TODO: Implement wait_for_data");
  return NULL;
}

void send_data(Connection *this, const char *data)
{
  printf("TODO: Implement send_data");
}

