#include "UrlManager.h"



HttpServer* UrlManager::getHttpServer(::std::string name){
    if(mp.find(name) == mp.end())return nullptr;
    return mp[name];
}
void UrlManager::addHttpServer(HttpServer* url){
    mp[url->getUrl()] = url;
}

UrlManager* UrlManager::instance = nullptr;

UrlManager* UrlManager::getInstance(){
    if(instance == nullptr)instance = new UrlManager();
    return instance;
}

UrlManager::UrlManager(){ }
