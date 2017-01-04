#include "entrance-protocol.h"

#include <asio.hpp>
#include <cstring>

// project includes
extern "C" {
#include "entrance-request.h"
#include "entrance-response.h"
#include "utils.h"
}

/**
 * @brief The value given here is mostly arbitarary; I just want to put a limit
 * on it so that I don't have to dynamically manage memory, as that is
 * inefficient.
 */
const int ATTENDANT_NAME_LENGTH = ATTENDANT_NAME_LENGTH_MACRO;

using asio::io_service;
static io_service service;

/*****************************************************************************/
/*                         HELPER FUNCTION DECLARATIONS                      */
/*****************************************************************************/
asio::ip::udp::endpoint make_endpoint(const char *host, unsigned port);
int min(int, int);

/*****************************************************************************/
/*                       ENTRANCE REUQEST IMPLEMENTATION                     */
/*****************************************************************************/
const char *get_attendant_name(const EntranceRequest *er)
{
  return er->attendant_name;
}

void free_entrance_request(EntranceRequest *er)
{
  delete er;
}

EntranceRequest *receive_entrance_request(unsigned port)
{
  using asio::buffer;
  using asio::ip::udp;
  using asio::error_code;

  EntranceRequest *ret = new EntranceRequest();

  udp::socket socket(service, udp::endpoint(udp::v4(), port));
  udp::endpoint remote_endpoint;
  error_code error;

  socket.receive_from(buffer(ret, sizeof(EntranceRequest)), remote_endpoint, 0,
                      error);

  if (error)
  {
    free_entrance_request(ret);
    ret = nullptr;
  }

  return ret;
}

int send_entrance_request(const char *server_name, unsigned server_port,
                           const char *attendant_name, unsigned local_port)
{
  try
  {
    using asio::buffer;
    using asio::ip::udp;

    EntranceRequest to_send;
    memset(to_send.attendant_name, 0, sizeof(to_send.attendant_name));
    strncpy(to_send.attendant_name, attendant_name, ATTENDANT_NAME_LENGTH);
    memset(to_send.host, 0, sizeof(to_send.host));
    to_send.port = local_port;

    udp::endpoint local_endpoint(udp::v4(), local_port);
    udp::endpoint remote_endpoint = make_endpoint(server_name, server_port);

    udp::socket socket(service, local_endpoint);
    socket.send_to(buffer(&to_send, sizeof(to_send)), remote_endpoint);
    return true;
  }
  catch (std::exception &e)
  {
    return false;
  }
}

/*****************************************************************************/
/*                       ENTRANCE REUQEST IMPLEMENTATION                     */
/*****************************************************************************/
unsigned get_port(const EntranceResponse *er)
{
  return er->port;
}

EntranceResponse *receive_entrance_response(unsigned port)
{
  using asio::buffer;
  using asio::ip::udp;
  using asio::error_code;

  EntranceResponse *ret = new EntranceResponse();

  udp::socket socket(service, udp::endpoint(udp::v4(), port));
  udp::endpoint remote_endpoint;
  error_code error;

  socket.receive_from(buffer(ret, sizeof(EntranceResponse)), remote_endpoint, 0,
                      error);

  if (error)
  {
    free_entrance_response(ret);
    ret = nullptr;
  }

  return ret;
}

void send_entrance_response(EntranceRequest *respondee, unsigned attendant_port)
{
  using asio::buffer;
  using asio::ip::udp;

  EntranceResponse to_send;
  to_send.port = attendant_port;

  udp::endpoint local_endpoint(udp::v4(), 0);
  udp::endpoint remote_endpoint = make_endpoint(respondee->host,
                                                respondee->port);

  udp::socket socket(service, local_endpoint);
  socket.send_to(buffer(&to_send, sizeof(to_send)), remote_endpoint);
}

void free_entrance_response(EntranceResponse *er)
{
  delete er;
}

/*****************************************************************************/
/*                         HELPER FUNCTION DEFINITIONS                       */
/*****************************************************************************/
asio::ip::udp::endpoint make_endpoint(const char *host, unsigned port)
{
  using asio::ip::udp;

  static char port_string[10];
  memset(port_string, 0, sizeof(port_string));
  utoa(port, port_string);

  static udp::resolver res(service);
  return *res.resolve(udp::resolver::query(udp::v4(), host, port_string));
}

int min(int i1, int i2)
{
  if (i1 < i2)
    return i1;
  else
    return i2;
}

