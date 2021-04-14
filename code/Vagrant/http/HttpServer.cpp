#include"HttpServer.h"

HttpServer::HttpServer(::std::string url)
: m_url(url) { }

::std::string HttpServer::getUrl(){
   return m_url;
}

bool HttpServer::doGet(HttpRequest &req,HttpResponse &resp){ return false; }
bool HttpServer::doPost(HttpRequest &req,HttpResponse &resp){ return false; }