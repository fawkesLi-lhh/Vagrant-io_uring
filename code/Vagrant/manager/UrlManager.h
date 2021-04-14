#ifndef _URLMANAGER_H_
#define _URLMANAGER_H_

#include <map>

#include "../http/HttpServer.h"

class UrlManager {
public:
   static UrlManager* getInstance();
   HttpServer* getHttpServer(::std::string);
   void addHttpServer(HttpServer* url);
private:
   UrlManager();
   ::std::map<::std::string,HttpServer*> mp;
   static UrlManager* instance;
};



#endif
