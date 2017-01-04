#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct Attendant Attendant;

typedef struct Data Data;
struct Data
{
  char *buffer;
  size_t length;

  virtual ~Data();
};

typedef void (*SendData)(Data *);
typedef Data *(*WaitForData)();
typedef void (*Stop);

Attendant *init(SendData send_data, WaitForData wait_for_data);
void start();
bool validate_data(Attendant *, const Data *);
Data  *transform_incoming_data(Attendant *, Data *);
Data  *transform_outgoing_data(Attendant *, Data *);
void stop(Attendant *);

