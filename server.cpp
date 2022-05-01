#include "server.h"
#include "helper.h"
#include "./parser/parser.h"
#include "./command/command.h"

#include <string>
#include <cstring>
#include <regex>
#include <vector>

int Server::ID = 1110;

/***********
the transmitted class must have
this functions parse_code() and get_tokens()
************/
template <class Parser = myDB::Parser>  
static void* serverThreadRoutine(void *arg)
{
  int _connfd = *(int*)arg;
  pthread_detach(pthread_self());

  if (_connfd < 0)
  {
    std::cerr <<  "ERROR on listen";
    exit(1);
  }

  int number = ++Server::ID;
  char getLine[MAXLINE];
  int pid, recvLine_len, n;
  
  Parser pars;
  std::vector<std::string> tokens;
  myDB::Command command;

  while (true)
  {
    bzero(getLine, MAXLINE);
    n = recv(_connfd, getLine, MAXLINE, 0);

    if (n < 0)
    {
      std::cerr << "ERROR on read";
      break;                        
    }
    
    std::string recvLine(getLine);
    pars.parse_code(recvLine);

    recvLine = command.coll_command(pars.get_tokens());
    
    recvLine += "\r\n";
    send(_connfd, recvLine.c_str(), recvLine.size(), 0);
  }

  close(_connfd);
  free(arg);
  return 0;
}

Server::Server(std::string IP_addres, int port)
{
  static const int SERVER_PORT = port;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0)
  {
    std::cerr << "Error opening socket\n";
    std::exit(1);
  }
  
  bzero((char *) &servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(IP_addres.c_str());
  servAddr.sin_port = htons(SERVER_PORT);
  
  if (bind(listenfd, (sockaddr *) &servAddr, sizeof(servAddr)) < 0)
  {
    std::cerr << "ERROR on binding\n";
    exit(1);
  }
  
  std::cout << "server ip : " << inet_ntoa(servAddr.sin_addr) << std::endl;
  if (listen(listenfd, 5) < 0)
  {
    std::cerr << "ERROR on listen\n";
    exit(1);
  }
}

void Server::acceptClients()
{
  while (true)
  {
    socklen_t client_len = sizeof(cliAddr);
    connfd = (int*)malloc(sizeof(int));
    *connfd = accept(listenfd, (sockaddr *)&cliAddr, &client_len);
    if (listen(listenfd, 5) < 0)
    {
    std::cerr << "ERROR on listen\n";
    exit(1);
    }
    pthread_create(&tid, NULL, serverThreadRoutine, (void*)connfd);
  }
}
