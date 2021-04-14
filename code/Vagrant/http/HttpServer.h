#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_

#include <string>
#include"HttpRequest.h"
#include"HttpResponse.h"

/*
Don't declare member variables in subclasses of this class,
Otherwise,there will be unpredictable errors
*/

class HttpServer{
public:
   HttpServer(::std::string url);
   virtual bool doGet(HttpRequest &req,HttpResponse &resp);
   virtual bool doPost(HttpRequest &req,HttpResponse &resp);
   ::std::string getUrl();
private:
   ::std::string m_url;
};

#endif