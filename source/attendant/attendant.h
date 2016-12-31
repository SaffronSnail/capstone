#pragma once

#include <stdbool.h>
#include <stddef.h>

struct Attendant;

typedef struct Data Data;
struct Data
{
  char *buffer;
  size_t length;

  void (*free)(Data);
};

typedef struct
{
  const char *buffer;
  const size_t length;
} ConstData;

void init();
bool validate_data(ConstData);
void transform_data(Data);
void receive_data(Data);
void close();

void send_data(Data);

