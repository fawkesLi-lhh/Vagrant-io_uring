#include "HttpResponse.h"

#include<cstring>
#include <cstdio>

const char *head_200 = "HTTP/1.1 200 OK\nConnection: keep-alive\n";
const char *head_404 = "HTTP/1.1 404 Not Found\nConnection: keep-alive\n";
const char *val_404 = "The requested file was not found on this server.";

HttpResponse::HttpResponse(){
    memset(data,0,sizeof(char)*4100);
    memset(head,0,sizeof(char)*4100);
}

void HttpResponse::init(RESPONSE_METHOD method){
    m_method = method;
    file = nullptr;
    if(method == m_200) {
        strcpy(head,head_200);
        memset(data,0,4100*sizeof(char));
    }
    else {
        strcpy(head,head_404);
        strcpy(data,val_404);
    }
}

void HttpResponse::addHead(const char *str){
    strcat(head,str);
    strcat(head,"\n");
}
void HttpResponse::updateData(const char *str){
    strcpy(data,str);
}

void HttpResponse::updateFile(char *str,int len){
    file = str;
    fileLenght = len;
}

void HttpResponse::finish(){
    if(file == nullptr){
        file = data;
        fileLenght = strlen(data);
    }
    char buffer[555];
    sprintf(buffer,"Content-Length: %d\n",fileLenght);
    addHead(buffer);
}

