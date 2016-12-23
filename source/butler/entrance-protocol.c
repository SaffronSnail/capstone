// related header
#include "entrance-protocol.h"

// standard c includes
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// project includes
#include "entrance-request.h"
#include "entrance-response.h"
#include "networking.h"

/**
 * @brief The value given here is mostly arbitarary; I just want to put a limit
 * on it so that I don't have to dynamically manage memory, as that is
 * inefficient.
 */
const int ATTENDANT_NAME_LENGTH = ATTENDANT_NAME_LENGTH_MACRO;

/*****************************************************************************/
/*                         HELPER FUNCTION DECLARATIONS                      */
/*****************************************************************************/
int min(int, int);

/*****************************************************************************/
/*                       ENTRANCE REUQEST IMPLEMENTATION                     */
/*****************************************************************************/
const char *get_attendant_name(const EntranceRequest *this)
{
  return this->attendant_name;
}

void free_entrance_request(EntranceRequest **this)
{
  free(*this);
  *this = NULL;
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
unsigned get_port(const EntranceResponse *this)
{
  return this->port;
}

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

void free_entrance_response(EntranceResponse **this)
{
  free(*this);
  *this = NULL;
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

