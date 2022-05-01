#include "client.h"
#include "helper.h"

#include <iostream>
#include <string>

Client::Client(std::string IP_addres, int port)
{
  serverIp = IP_addres;
  static const int SERVER_PORT = port;
  
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    std::cerr << "Error while creating socket\n";
    exit(1);
  }
  
  bzero(&serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(SERVER_PORT);
  
  if (inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr) <= 0)
  {
    std::cerr << "inet_pton error\n";
    exit(1);
  }
  if (connect(sockfd, (SA *) &serverAddr, sizeof(serverAddr)) < 0)
  {
    std::cerr << "connect failed\n";
    exit(1);
  }
}

void Client::sendAndRecv(const std::string& sendLine)
{
  int n {};
  this->sendLine = sendLine;
  if (send(sockfd, sendLine.c_str(), sendLine.size(), 0) != sendLine.size())
  {
    std::cerr << "write error\n";
    exit(1);
  }
  
  char ch;
  while ((n = recv(sockfd, &ch, 1, 0)))
  {
    if (ch == '\r') break;
    std::cout << ch;
  }
  
  if (n < 0)
  {
    std::cerr << "read error\n";
    exit(1);
  }
}
