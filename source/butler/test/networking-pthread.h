#pragma once

#include "log.h"
#include "networking.h"

typedef struct
{
  PORT port;
  Datagram receive;
} ListenerInput;

void *receive_datagram_pthread(void *in)
{
  ListenerInput *input = static_cast<ListenerInput *>(in);
  log("passing in port %u", input->port);
  input->receive = receive_datagram(input->port);
  return NULL;
}


