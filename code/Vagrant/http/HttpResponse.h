#ifndef _HTTPRESPONSE_H_
#define _HTTPRESPONSE_H_

enum RESPONSE_METHOD {m_404 = 0,m_200 = 1};

class HttpResponse{
public:
    HttpResponse();
    void init(RESPONSE_METHOD method);
    void addHead(const char *str);
    void updateData(const char *str);
    void updateFile(char *str,int len);
    void finish();
public:
    char head[4100], data[4100],*file;
    int fileLenght;
private:
    RESPONSE_METHOD m_method;
};

#endif

