#include"Server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <errno.h>

#include <iostream>
#include <chrono>

#include "../config/Config.h"

Server::Server(){
    initSocket(Config::getInstance()->getPort());
    uringer.init(4100);
    uringer.addPoll(listenfd,POLLIN,std::bind(&Server::dealListen,this));
    uringer.submit();
}

void Server::loop(){
    while(1){
        struct io_uring_cqe *cqe = uringer.peek_cqe();
        if(cqe == nullptr){
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }
        uringer.finishEvent(cqe->user_data);
        uringer.cqe_seen(cqe);
        uringer.submit();
    }
}

void Server::initSocket(int port){
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server;
    socklen_t addrlen;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listenfd,(struct sockaddr*)&server,sizeof(server));
    listen(listenfd,6);
}

void Server::dealListen(){
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof(client_address);
    int connfd = accept(listenfd, ( struct sockaddr* )&client_address, &client_addrlength);
    if(connfd < 0 ){
       printf( "errno is: %d\n", errno);
       return;
    }
    connectPool[connfd] = client_address;
    uringer.addPoll(connfd,POLLIN,std::bind(&Server::dealConnectPollIn,this,connfd));
    uringer.addPoll(listenfd,POLLIN,std::bind(&Server::dealListen,this));
}

void Server::dealConnectPollIn(int fd){
    HttpProcess *pro = new HttpProcess(fd,connectPool[fd]);
    uringer.addRead(fd,pro->req.data,4000,0,
        std::bind(&Server::dealRead,this,fd,pro));
}
void Server::dealRead(int fd,HttpProcess* pro){
    threadPool.AddTask(std::bind(&HttpProcess::process,pro,&uringer));
    uringer.addPoll(fd,POLLIN,std::bind(&Server::dealConnectPollIn,this,fd));
}