// related header
#include "entrance-protocol.h"

// standard c includes
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// project includes
#include "networking.h"


#define ATTENDANT_NAME_LENGTH_MACRO 255

/**
 * @brief The value given here is mostly arbitarary; I just want to put a limit
 * on it so that I don't have to dynamically manage memory, as that is
 * inefficient.
 */
const int ATTENDANT_NAME_LENGTH = ATTENDANT_NAME_LENGTH_MACRO;

#define HOSTNAME_LENGTH_MACRO 255
/**
 * @brief This name is based on RFC 1035, which states that names should "255
 * octets or less". This value should only change if the standard changes, as
 * code may (at time of writing, some code does) rely on knowing that buffers
 * can hold valid hostnames of any length.
 */
const int HOSTNAME_LENGTH = HOSTNAME_LENGTH_MACRO;

/*****************************************************************************/
/*                         HELPER FUNCTION DECLARATIONS                      */
/*****************************************************************************/
int min(int, int);

struct EntranceRequest
{
  /**
   * @brief The attendant that the client wants to talk to
   */
  char attendant_name[ATTENDANT_NAME_LENGTH_MACRO + 1];

  /**
   * @brief The hostname of the client
   */
  char host[HOSTNAME_LENGTH_MACRO + 1];

  /**
   * @brief The port of the client
   */
  unsigned port;
};

struct EntranceResponse
{
  /**
   * @brief the port that the server is listening on
   */
  unsigned port;
};

/*****************************************************************************/
/*                       ENTRANCE REUQEST IMPLEMENTATION                     */
/*****************************************************************************/
const char *get_attendant_name(const EntranceRequest *this)
{
  return this->attendant_name;
}

EntranceRequest *receive_entrance_request(unsigned port)
{
  EntranceRequest *ret = (EntranceRequest *)malloc(sizeof(EntranceRequest));
  *ret = *(EntranceRequest *)receive_datagram(port).data;
  return ret;
}

void send_entrance_request(const char *attendant_name,
                           const char *host, unsigned remote_port,
                           unsigned local_port)
{
  Datagram dg;
  EntranceRequest to_send;

  /* initialize the request */
  // strncpy does NOT guarantee a null character at the end
  strncpy(to_send.attendant_name, attendant_name, ATTENDANT_NAME_LENGTH);
  to_send.attendant_name[ATTENDANT_NAME_LENGTH] = 0;

  // gethostname also does NOT guarantee a NULL at the end when the hostname
  // is truncated, but HOSTNAME_LENGTH is based on the maximum
  gethostname(to_send.host, HOSTNAME_LENGTH + 1);

  to_send.port = local_port;

  /* send the request */
  static_assert(sizeof(EntranceResponse) <= MAX_MESSAGE_LENGTH_MACRO,
      "EntranceResponse it too large to fit into one message!");

  memcpy(dg.data, &to_send, sizeof(EntranceRequest));
  dg.length = sizeof(EntranceRequest);
  send_datagram(dg, host, remote_port);
}

/*****************************************************************************/
/*                       ENTRANCE REUQEST IMPLEMENTATION                     */
/*****************************************************************************/
EntranceResponse *receive_entrance_response(unsigned port)
{
  EntranceResponse *response =
    (EntranceResponse *)malloc(sizeof(EntranceResponse));
  *response = *(EntranceResponse *)receive_datagram(port).data;

  return response;
}

void send_entrance_response(EntranceRequest *respondee, unsigned port)
{
  Datagram dg;
  EntranceResponse to_send;
  to_send.port = port;

  memcpy(dg.data, &to_send, sizeof(EntranceRequest));
  dg.length = sizeof(EntranceRequest);
  send_datagram(dg, respondee->host, respondee->port);
}

/*****************************************************************************/
/*                         HELPER FUNCTION DEFINITIONS                       */
/*****************************************************************************/
int min(int i1, int i2)
{
  if (i1 < i2)
    return i1;
  else
    return i2;
}

