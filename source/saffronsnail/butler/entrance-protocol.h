#pragma once

/*
 * The entrance protocol defines what happens during initial contact between
 * butler and a user; the user sends a request for an attendant and butler
 * tells the user what port the attendant is listening on
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The EntranceRequest is sent by the client to the server to indicate
 * (1) that it wants a connection and (2) which kind of attendant it wants to
 * tend to the connection
 */
typedef struct EntranceRequest EntranceRequest;

/**
 * @brief The EntranceResponse is sent by the server to the client after it
 * processes an EntranceRequest. It tells the lient 
 */
typedef struct EntranceResponse EntranceResponse;

/**
 * @brief The maximum length that an attendant's name can be; that is, it is
 * the number of characters that an attendant name can have, it does not
 * include the NULL character of c-strings or any other implementation-specific
 * considerations.
 */
extern const int ATTENDANT_NAME_LENGTH;

/** \definegroup EntranceRequest
 * @{
 */

/**
 * @brief creates an EntranceRequest and send it to the specified host and
 * port. Blocks until a response is received.
 *
 * @param attendant_name The name of the attendent you are requesting
 * @param host the name (IP address, URL, etc.) of the server
 * @param remote_port the port the server is listening on
 * @param local_port the port that the server should send the EntranceResponse
 *        to
 *
 * @return 0 if there was no error, otherwise a negative number
 */
int send_entrance_request(const char *server_name, unsigned server_port,
                          const char *attendant_name, unsigned local_port);

/**
 * @brief Blocks until a message is received on the given port; it is assumed
 * to be a valid request for an attendant.
 *
 * @param port the port to listen on
 *
 * @return a pointer to the data about the request; the caller is responsible
 * for freeing this data wit hteh free_entrance_request function, below
 */
EntranceRequest *receive_entrance_request(unsigned port);

const char *get_attendant_name(const EntranceRequest *);

/**
 * @brief frees the memory associated with the entrance request
 *
 * @param the memory that should be freed
 */
void free_entrance_request(EntranceRequest *target);

/**@}*/ //EntranceRequest group

/** \definegroup EntranceResponse
 * @{
 */

/**
 * @brief Notifies the send of the port that is listening
 *
 * @param respondee The request that is being responded to
 * @param port the port that is being listened on
 */
void send_entrance_response(EntranceRequest *respondee, unsigned port);

EntranceResponse *receive_entrance_response(unsigned port);

unsigned get_port(const EntranceResponse *);

/**
 * @brief frees the memory associated with the entrance response
 *
 * @param the memory that should be freed
 */
void free_entrance_response(EntranceResponse *target);

/**@}*/ //EntranceResponse group

#ifdef __cplusplus
} //extern "C"
#endif

