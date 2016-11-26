// related header
#include "entrance-protocol.h"

// standard c includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*****************************************************************************/
/*                             CONSTANT DEFINITIONS                          */
/*****************************************************************************/
const int ATTENDANT_NAME_LENGTH = 255;
#define ATTENDANT_BUFFER_LENGTH (ATTENDANT_NAME_LENGTH + 1)

/*****************************************************************************/
/*                              STRUCT DEFNITIONS                            */
/*****************************************************************************/
typedef struct EntranceRequest
{
  char *attendant_name;
} EntranceRequest;

typedef struct EntranceResponse
{
  int port;
} EntranceResponse;

/*****************************************************************************/
/*                         HELPER FUNCTION DECLARATIONS                      */
/*****************************************************************************/
int min(int, int);

/*****************************************************************************/
/*                       ENTRANCE REUQEST IMPLEMENTATION                     */
/*****************************************************************************/
EntranceRequest *create_entrance_request(const char *attendant_name)
{
  return read_entrance_request(attendant_name, strlen(attendant_name));
}

EntranceRequest *read_entrance_request(const char *data, int data_length)
{
  EntranceRequest *ret = (EntranceRequest *)malloc(sizeof(EntranceRequest));

  ret->attendant_name = (char *)malloc(sizeof(char) * ATTENDANT_BUFFER_LENGTH);
  memset(ret->attendant_name, 0, ATTENDANT_BUFFER_LENGTH);

  memcpy(ret->attendant_name, data, min(data_length, ATTENDANT_NAME_LENGTH));

  return ret;
}

const char *get_attendant_name(EntranceRequest *this)
{
  return this->attendant_name;
}
  
/*****************************************************************************/
/*                       ENTRANCE RESPONSE IMPLEMENTATION                    */
/*****************************************************************************/
EntranceResponse *create_entrance_response(int port)
{
  EntranceResponse *ret = (EntranceResponse *)malloc(
                                              sizeof(EntranceResponse)
  );

  ret->port = port;
  return ret;
}

EntranceResponse *read_entrance_response(const char *data, int data_length)
{
  // if we have less than 8 bytes the cast in the else branch is dangerous
  if (data_length < 8)
  {
    fprintf(stderr,
            "An entrance response must be 8 bytes in length! Yours is %D.",
            data_length
    );

    return NULL;
  }
  else
    return create_entrance_response(*(int *)data);
}

int get_port(EntranceResponse *this)
{
  return this->port;
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

