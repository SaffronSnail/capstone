#pragma once

#include <stdbool.h>
#include <stddef.h>

/*
 * This interface manages networking through a 'Connection' abstraction; the
 * idea is that this module hides all platform-specific networking code while
 * being as low-level as possible.
 */

typedef struct
{
  const char *data;
  size_t length;
} Datagram;

/* CONNECTION-BASED */
// This contains the information necesarry for the platform the code is
// implemented for
typedef struct Connection Connection;

// Blocks until a new connection is recieved on the given port
Connection *wait_for_connection(unsigned port);

// Connects to the given host on the given port. Returns NULL if connection
// can't be made.
Connection *connect_to_host(const char *host, unsigned port);

// blocks until the buffer is full (TODO: redsign this function...)
void receive_data(Connection *, const char *buffer, int buffer_size);

// send the bytes contained in the buffer data
void send_data(Connection *, Datagram data);

/* NON-CONNECTION BASED */
Datagram receive_datagram(unsigned port);
bool send_datagram(Datagram data, const char *host, unsigned port);

