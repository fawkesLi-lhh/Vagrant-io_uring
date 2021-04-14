#ifndef _HTTPPROCESS_H_
#define _HTTPPROCESS_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../manager/UrlManager.h"
#include "../io/Uringer.h"

class HttpProcess
{
public:
    HttpProcess(int socketFd,struct sockaddr_in address);
    void process(Uringer* uringer);
public:
    HttpRequest req;
    HttpResponse resp;
private:
    int fd;
    struct sockaddr_in client_address;
    iovec io[2];
};

void finish(HttpProcess* pro);


#endif
