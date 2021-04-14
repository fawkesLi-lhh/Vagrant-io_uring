#include "HttpProcess.h"

#include "../manager/AssetManager.h"

#include <cstring>

HttpProcess::HttpProcess(int socketFd,struct sockaddr_in address)
:fd(socketFd),client_address(address){ }

void HttpProcess::process(Uringer* uringer){
    req.init();
    resp.init(m_404);
    File file = AssetManager::getInstance()->getFile(req.getUrl());
    HttpServer* url = UrlManager::getInstance()->getHttpServer(req.getUrl());
    if(file.data!=nullptr){
        resp.init(m_200);
        resp.updateFile(file.data,file.len);
    }
    else if(url!=nullptr){
        if(req.getMethod() == GET) resp.init(m_200),url->doGet(req,resp);
        else if(req.getMethod() == POST) resp.init(m_200),url->doPost(req,resp);
    }
    resp.finish();
    io[0].iov_base = resp.head; io[0].iov_len = strlen(resp.head);
    io[1].iov_base = resp.file; io[1].iov_len = resp.fileLenght;
    uringer->addWriteV(fd,io,2,0,::std::bind(finish,this));
    uringer->submit();
}

void finish(HttpProcess* pro){
    delete pro;
}
