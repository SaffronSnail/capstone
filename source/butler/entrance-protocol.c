// related header
#include "entrance-protocol.h"

// standard c includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// project includes
#include "networking.h"


/**
 * @brief The value given here is mostly arbitarary; I just want to put a limit
 * on it so that I don't have to dynamically manage memory, as that is
 * inefficient.
 */
const int ATTENDANT_NAME_LENGTH = 255;

/*****************************************************************************/
/*                         HELPER FUNCTION DECLARATIONS                      */
/*****************************************************************************/
int min(int, int);

struct EntranceRequest
{
  /**
   * @brief The attendant that the client wants to talk to
   */
  const char *attendant_name;

  /**
   * @brief The hostname of the client
   */
  const char *host;

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
EntranceResponse *send_entrance_request(const char *attendant_name,
                                        const char *host, unsigned port)
{
  Datagram dg;
  dg.data   = attendant_name;
  dg.length = strlen(attendant_name);
  send_datagram(dg, host, port);
  
  dg = receive_datagram(port);
  EntranceResponse *response = (EntranceResponse *)malloc(sizeof(EntranceResponse));
#error set the data of EntranceResponse!
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

