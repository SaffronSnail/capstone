#include "attendant.h"

#include <iostream>

struct Attendant
{
  SendData send_data;
  WaitForData wait_for_data;

  Attendant(SendData s, WaitForData w) : send_data(s), wait_for_data(w)
  {
  }
};

static Data *create_data(char *buffer, size_t length)
{
  Data *ret = new Data;
  ret->length = length;
  ret->buffer = buffer;
  ret->destructor = [] (Data *d) { delete d->buffer; delete d; };
  return ret;
}

Attendant *init(SendData send_data, WaitForData wait_for_data)
{
  return new Attendant(send_data, wait_for_data);
}

void start(Attendant *att)
{
  att->wait_for_data();
}

bool validate_data(Attendant *, const Data *data)
{
  return data->buffer[data->length - 1] == '\0';
}

static Data *ensure_null_character(Data *data)
{
  if (data->buffer[data->length - 1] == '\0')
    return data;
  else
  {
    char *buffer = new char[data->length + 1];
    buffer[data->length] = '0';
    auto ret = create_data(buffer, data->length + 1);
    data->destructor(data);
    return ret;
  }
}

Data *transform_incoming_data(Attendant *, Data *data)
{
  return ensure_null_character(data);
}

Data *transform_outgoing_data(Attendant *, Data *data)
{
  return ensure_null_character(data);
}

void receive_data(Attendant *att, Data data)
{
  std::cout << data.buffer << std::endl;
  att->send_data(&data);
  att->wait_for_data();
}

void stop(Attendant *me)
{
  delete me;
}

