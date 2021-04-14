#ifndef _SERVER_H_
#define _SERVER_H_

#include "../io/Uringer.h"
#include "../pool/ThreadPool.h"
#include "../http/HttpProcess.h"

class Server
{
public:
   Server();
   void loop();
private:
   void initSocket(int port);
   void dealListen();
   void dealConnectPollIn(int fd);
   void dealRead(int fd,HttpProcess* pro);
private:
   int listenfd;
   Uringer uringer;
   ThreadPool threadPool;
   ::std::map<int,struct sockaddr_in> connectPool;
};


#endif
