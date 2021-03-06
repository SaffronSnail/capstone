#pragma once

#include "entrance-protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ATTENDANT_NAME_LENGTH_MACRO 255

#define HOSTNAME_LENGTH_MACRO 255
/**
 * @brief This name is based on RFC 1035, which states that names should "255
 * octets or less". This value should only change if the standard changes, as
 * code may (at time of writing, some code does) rely on knowing that buffers
 * can hold valid hostnames of any length.
 */
const int HOSTNAME_LENGTH = HOSTNAME_LENGTH_MACRO;

/**
 * @brief This is the first message sent which indicates to a server running a
 * butler listener that the client is interested in forming a connection with an
 * attendant.
 */
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

#ifdef __cplusplus
} // extern "C"
#endif

