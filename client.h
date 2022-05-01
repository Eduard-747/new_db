#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstring>
#include <iostream>
#include <string>

typedef sockaddr SA;
const int MAXLINE = 255;

class Client
{
public:
  Client( std::string,int);
  void sendAndRecv(const std::string&);
  ~Client() = default;
private:
  int sockfd;
  sockaddr_in serverAddr;
  std::string serverIp;
  char recvLine[255];
  std::string sendLine;
};

#endif // CLIENT_H
