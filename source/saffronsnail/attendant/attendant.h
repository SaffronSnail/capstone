#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

  /**
   * @brief This structure is defined separately by each attendant
   * implementation; this means that problems will occur if attendants are
   * unwittingly shared between different attendant modules; for this reason,
   * butler is careful to associate attendants with the modules that defined
   * them, and any framework that uses attendants should do the same
   */
typedef struct Attendant Attendant;

struct Data
{
  /**
   * @brief The data that is being communicated
   */
  char *buffer;
  /**
   * @brief The number of bytes in the buffer
   */
  size_t length;

  /**
   * @brief A function that frees any dynamically-allocated memory, analgous to
   * a c++ destructor
   *
   * @param me this paramater should always be the data structure containing it;
   * if c++ supported closures this field would be useless
   */
  void (*destructor)(Data *me);
};
typedef struct Data Data;

typedef void (*SendData)(Data *);
typedef Data *(*WaitForData)();
typedef void (*Stop);

/**
 * @brief This function behaves as a constructor for Attendants; WARNING: a
 * module that calls either send_data or wait_for_data in this function is
 * misbehaving (these callbacks should be stored in the attendant for future
 * use)
 *
 * @param send_data a callback that allows the attendant to send data to it's
 * client
 * @param wait_for_data a callback that allows the attendant to received data
 * from it's client
 *
 * @return a fully initialized attendant
 */
Attendant *init(SendData send_data, WaitForData wait_for_data);
/**
 * @brief When this is called the attendant should begin communicating with the
 * client. After this point, butler will stop interacting with communication
 * between the client and the attendant except for ensuring that the transform
 * callbacks are called at the appropriate times (see below)
 *
 * @param The attendant to start
 */
void start(Attendant *);
/**
 * @brief This function should ensure that data is correctly formed, but should
 * not contain complex logic or modify the data. For more details, refer to
 * https://msdn.microsoft.com/en-us/library/ms952652.aspx and read the section
 * on The Business Rules Later
 *
 * @param The attendant that should validate the data
 * @param The data to be validated
 *
 * @return True if the data is valid, false if it is not
 */
bool validate_data(Attendant *, const Data *);
/**
 * @brief Takes data formatted for communication and formats it for processing;
 * some attendants may need to do anything in this step, in which case they
 * should simply return the data passed in. If new data is created, be sure to
 * call the passed-in data's destructor
 *
 * @param The attendant that hsould transform the data
 * @param The data to be transformed
 *
 * @return Data in processing format
 */
Data *transform_incoming_data(Attendant *, Data *);
/**
 * @brief Takes data formatted for processing and formats it for communication;
 * some attendants may not need to do anything in this step, in which case they
 * should simply return the data passed in. If new data is created, be sure to
 * call the passed-in data's destructor
 *
 * @param The attendant that should transform the data
 * @param The data to be transformed
 *
 * @return Data in communication format
 */
Data *transform_outgoing_data(Attendant *, Data *);
/**
 * @brief This signals to the attendant that it should perform necesarry cleanup
 * work before the connection is terminated
 *
 * @param The attendant to close
 */
void stop(Attendant *);

#ifdef __cplusplus
} // extern "C"
#endif

