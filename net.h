typedef int  Connection
typedef char Byte;

struct ByteArray { Byte *data, int length; }

// the returned connection may contain an error code
Connection connection_construct(int port);
ByteArray  connection_read     (Connection);
void       connection_write    (Connection, ByteArray);

ByteArray byte_array_construct(Byte *data, int length);

ByteArray byte_array_construct(int length);
// only use this if you didn't pass in your own data
// (if you used the one-argument constructor)
void byte_array_destruct (ByteArray);

void byte_array_set      (ByteArray, int index, Byte value);
Byte byte_array_read     (ByteArray, int index);

