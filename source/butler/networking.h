#pragma once

/*
 * This interface manages networking through a 'Connection' abstraction; the
 * idea is that this module hides all platform-specific networking code while
 * being as low-level as possible.
 */

// This contains the information necesarry for the platform the code is
// implemented for
typedef struct Connection Connection;

// Blocks until a new connection is recieved on the given port
Connection *wait_for_connection(int port);

// blocks until the buffer is full (TODO: redsign this function...)
void wait_for_data(Connection *, const char *buffer, int buffer_size);

// send the bytes contained in the buffer data
void send_data    (Connection *, const char *data, int data_length);

