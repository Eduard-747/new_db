#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

const int  MAXLINE = 255;

class Server
{
public:
  static int ID;
  Server(std::string,int);
  void acceptClients();
private:
  int listenfd;
  int *connfd;
  sockaddr_in servAddr;
  sockaddr_in cliAddr;
  pthread_t tid; 
};

#endif // SERVER_H