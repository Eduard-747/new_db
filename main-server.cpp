#include "server.h"

#include <string>

extern std::pair<std::string, int> data_parser();

int main()
{
  auto [IpAdress, port] = data_parser();
  Server socket (IpAdress, port);
  socket.acceptClients();
  
  return 0;
}
