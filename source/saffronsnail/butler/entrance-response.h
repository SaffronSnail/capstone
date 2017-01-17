#pragma once

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * @brief This message is how the server communicates information
   * necesarry for the client to connect to the attendant, once it
   * has been loaded.
   */
struct EntranceResponse
{
  /**
   * @brief the port that the server is listening on
   */
  unsigned port;
};

#ifdef __cplusplus
}
#endif

