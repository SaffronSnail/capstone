#pragma once

typedef struct Connection Connection;
typedef void (*Callback)(Connection *);

Connection *wait_for_connection(int port);
const char *wait_for_data      (Connection *, int buffer_size);
void        send_data          (Connection *, const char *data);

