extern "C" {
#include "attendant.hpp"
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

bool validate_data(Attendant *, const Data *)
{
  std::cout << "validate data called!" << std::endl;
  return true;
}

Data *transform_incoming_data(Attendant *, Data *ret)
{
  std::cout << "transform incoming data called!" << std::endl;
  return ret;
}

Data *transform_outgoing_data(Attendant *, Data *ret)
{
  std::cout << "transform outgoing data called!" << std::endl;
  return ret;
}

void stop(Attendant *)
{
  std::cout << "stop called!" << std::endl;
}

