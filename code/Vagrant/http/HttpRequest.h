#ifndef _HTTPREQUEST_H_
#define _HTTPREQUEST_H_

#include <string>

enum REQUEST_METHOD { GET = 0,POST = 1,HEAD = 2,PUT,DELETE,TRACE,OPTIONS,CONNECT,PATCH, UNKOWN};

class HttpRequest {
public:
    HttpRequest();
    void init();
    REQUEST_METHOD getMethod();
    char *getUrl();
    char *getHttpProtocol();
    char *getHost();
    char *getConnection();
    char *getCookie();
    char *getReferer();
    char *getOrigin();
    char *getParameter(const char *str);
public:
    char data[4100];
private:
    char message[4100];
    int conntentLength,strLength;
    REQUEST_METHOD method;
    char *url,*httpProtocol;
    char *host,*connection,*cookie,*referer,*origin,*conntent,str;
};

#endif
