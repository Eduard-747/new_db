#ifndef HELPER_H
#define HELPER_H

#include <utility>
#include <string>

std::pair<std::string, int> data_parser()
{
  std::string IpAdress = "192.168.10.229"; // Ipv4 address in PicsartAcademy
  int port = 7747; // random number :)  
  return std::make_pair(IpAdress, port);
}

#endif //HELPER_H