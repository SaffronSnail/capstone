extern "C" {
#include "attendant.h"
}

#include <iostream>
#include <string.h>

struct Attendant {};

Attendant *init(SendData, WaitForData)
{
  std::cout << "init called!" << std::endl;
  return NULL;
}

void start()
{
  std::cout << "start called!" << std::endl;
}

bool validate_data(Attendant *, ConstData)
{
  std::cout << "validate data called!" << std::endl;
  return true;
}

Data transform_incoming_data(Attendant *, Data)
{
  std::cout << "transform incoming data called!" << std::endl;
  Data ret;
  memset(&ret, 0, sizeof(ret));
  return ret;
}

Data transform_outgoing_data(Attendant *, Data)
{
  std::cout << "transform outgoing data called!" << std::endl;
  Data ret;
  memset(&ret, 0, sizeof(ret));
  return ret;
}

void stop(Attendant *)
{
  std::cout << "stop called!" << std::endl;
}

