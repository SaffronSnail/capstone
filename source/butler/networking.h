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

/** \definegroup ConnectionBased
 * @{ 
 */

/**
 * @brief Contains the information necesarry for the platform the code is
 *        implemented for
 */
typedef struct Connection Connection;

typedef unsigned Port;

/**
 * @brief blocks until a new connection is received
 *
 * @param port the port that should be listened on
 *
 * @return the first connection to be created after this function is called
 */
Connection *wait_for_connection(Port port);

// 
/**
 * @brief Connects to the given host on the given port. Returns NULL if
 * connection can't be made.
 *
 * @param host the name of the host to connect to
 * @param port the port of the host to connect to
 *
 * @return A pointer to a connection if one was successfully established, NULL
 * otherwise
 */
// 
Connection *connect_to_host(const char *host, Port port);

/**
 * @brief gracefully closes the connection, frees resources, and sets the
 * pointer to NULL
 *
 * @param connection the connection to be closed
 */
void close_connection(Connection **connection);

/**
 * @brief blocks until the buffer is full
 *
 * @param connection the connection that should wait for data
 * @param buffer the memory that should be filled
 * @param buffer_size the number of bytes that can be safely written to buffer
 */
void receive_data(Connection *connection, void *buffer, int buffer_size);

/**
 * @brief send the data on the given connection
 *
 * @param connection the connection to send the data on
 * @param data the data to send
 */
void send_data(Connection *connection, Datagram data);

/** #} */ //ConnectionBased group

/** \definegroup NonConnectionBased
 * @{ 
 */

Datagram receive_datagram(unsigned port);
bool send_datagram(void *data, size_t data_length, const char *host, Port port);

/** #} */ //NonConnectionBased group

