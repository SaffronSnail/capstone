// associated header
#include <"net.h">

// c standard libraries
#include <stdio.h>

// linux libraries
#include <sys/types.h>
#include <sys/socket.h>

struct Connection
{
	int sock;
};

Connection connection_construct(int port)
{
	Connection *my_ret = (Connectoin *)malloc(sizeof(Connection));
	my_ret->sock = socket(AF_INET, SOCK_RAW, 0);
	return my_ret;
}

ByteArray connection_read(Connection this)
{
	
}

void connection_write(Connection this, ByteArray data)
{

}

ByteArray byte_array_construct(Byte *data, int length)
{
	ByteArray ret;
	ret.data = data;
	ret.length = length;
	return ret;
}

ByteArray byte_array_cosntruct(int length)
{
	ByteArray ret;
	ret.data = malloc(sizeof(char) * length);
	ret.length = length;
	return ret;
}

void byte_array_destruct(ByteArray this)
{
	free(this.data);
}

void byte_array_set(ByteArray this, int index, Byte value)
{
	data[index] = value;
}

Byte byte_array_read(ByteArray this, int index)
{
	return this->data[index];
}

