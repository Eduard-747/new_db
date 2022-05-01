#include "client.h"

#include <string>
#include <iostream>

extern std::pair<std::string, int> data_parser();

int main()
{	
  auto [IpAdress, port] = data_parser(); // struct binding C++17
  
  Client socket(IpAdress, port);
  
  std::string str;
  while (str != "disconnect")
  {
    std::cout << "> ";
    std::getline(std::cin, str);
    
    socket.sendAndRecv(str);
  }
  
  return 0;
}
