#pragma once

#include <stdbool.h>
#include <stddef.h>

/*
 * This interface manages networking through a 'Connection' abstraction; the
 * idea is that this module hides all platform-specific networking code while
 * being as low-level as possible.
 */

/**
 * @brief We need a #define for this value because c doesn't always understand
 * that constants are constant when declaring arrays; however, const variables
 * are preferred to macros when they work
 */
#define MAX_MESSAGE_LENGTH_MACRO 1023
static const size_t MAX_MESSAGE_LENGTH = MAX_MESSAGE_LENGTH_MACRO;

typedef struct
{
  char data[MAX_MESSAGE_LENGTH_MACRO];
  size_t length;
} Datagram;


/* CONNECTION-BASED */
// This contains the information necesarry for the platform the code is
// implemented for
typedef struct Connection Connection;

typedef unsigned PORT;

// Blocks until a new connection is recieved on the given port
Connection *wait_for_connection(PORT port);

// Connects to the given host on the given port. Returns NULL if connection
// can't be made.
Connection *connect_to_host(const char *host, PORT port);

// blocks until the buffer is full (TODO: redsign this function...)
void receive_data(Connection *, const char *buffer, int buffer_size);

// send the bytes contained in the buffer data
void send_data(Connection *, Datagram data);

/* NON-CONNECTION BASED */
Datagram receive_datagram(unsigned port);
bool send_datagram(Datagram data, const char *host, PORT port);

