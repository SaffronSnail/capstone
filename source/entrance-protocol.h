#pragma once

/*
 * The entrance protocol defines what happens during initial contact between
 * butler and a user; the user sends a request for an attendant and butler
 * tells the user what port the attendant is listening on
 */

// The two fundamental data types for the Entrance protocol are the request
// and the response; this protocol should not require more than these two
// messages are passed
typedef struct EntranceRequest  EntranceRequest;
typedef struct EntranceResponse EntranceResponse;

// EntranceRequest functions
EntranceRequest *create_entrance_request(const char *attendant_name);
EntranceRequest *read_entrance_request  (const char *data, int data_length);
const char      *get_attendant_name     (EntranceRequest *);

// EntranceResponse functions
EntranceResponse *create_entrance_response(int port);
EntranceResponse *read_entrance_response  (const char *data, int data_length);
int               get_port                (EntranceResponse *);

