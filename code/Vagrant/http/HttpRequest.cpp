#include "HttpRequest.h"

#include <cstring>

HttpRequest::HttpRequest(){
   memset(data,0,sizeof(char)*4100);
   memset(message,0,sizeof(char)*4100);
}

void HttpRequest::init(){
    strcpy(message,data);
    int now = 0,stap = 0,len = strlen(message);
    for(int i = 0;i<len;i++){
        if(message[i] == ' ' && stap == 0){
         message[i] = '\0';
         if(strcmp(message+now,"GET") == 0) method = GET;
         else if(strcmp(message+now,"POST") == 0) method = POST;
         else if(strcmp(message+now,"HEAD") == 0) method = HEAD;
         else if(strcmp(message+now,"PUT") == 0) method = PUT;
         else if(strcmp(message+now,"DELETE") == 0) method = DELETE;
         else if(strcmp(message+now,"TRACE") == 0) method = TRACE;
         else if(strcmp(message+now,"OPTIONS") == 0) method = OPTIONS;
         else if(strcmp(message+now,"CONNECT") == 0) method = CONNECT;
         else if(strcmp(message+now,"PATCH") == 0) method = PATCH;
         else method = UNKOWN;
         stap++;
         now=i + 1;
      }
      else if(message[i] == ' ' &&stap == 1){
         message[i] = '\0';
         url=message+now;
         stap++;
         now=i + 1;
      }
      else if(message[i] == ' '||message[i] == '\n'){
         message[i] = '\0';
         httpProtocol=message+now;
         stap++;
         now=i + 1;
         break;
      }
    }
    for(int i = now;i<len;i++){
      if(message[i] == ':'){
         message[++i] ='\0';
         if(strcmp(message+now,"Host:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            host = message + now;
            now = i+1;
         }
         else if(strcmp(message+now,"Connection:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            connection =  message +now;
            now = i+1;
         }
         else if(strcmp(message+now,"Cookie:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            cookie = message + now;
            now = i+1;
         }
         else if(strcmp(message+now,"Referer:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            referer = message + now;
            now = i+1;
         }
         else if(strcmp(message+now,"Origin:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            origin = message + now;
            now = i+1;
         }
         else if(strcmp(message+now,"Content-Length:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            sscanf(message+now,"%d",&conntentLength);
            now = i+1;
         }
         else{
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            now = i+1;
         }
         if(message[i+1] == '\n') break;
      }
   }
   if(now >= len)return;
   conntent=message+(now+2);
   strLength = strlen(conntent);
   for(int i = now+1;i<len;i++){
      if(message[i] == '&'||message[i] == '='||message[i] == '\n'){
         message[i] = '\0';
      }
   }
}

char *HttpRequest::getParameter(const char *str){
    int now = 0;
    for(int i = 0;i<=strLength;i++){
        if(conntent[i] == '\0'){
            if(strcmp(conntent+now,str) == 0){
                return conntent+i+1;
            }
            else {
                while(conntent[++i]!='\0'&&i<=strLength);
                now = i+1;
            }
        }
    }
    return nullptr;
}

char *HttpRequest::getUrl(){
    return url;
}
char *HttpRequest::getHttpProtocol(){
    return httpProtocol;
}
char *HttpRequest::getHost(){
    return host;
}
char *HttpRequest::getConnection(){
    return connection;
}
char *HttpRequest::getCookie(){
    return cookie;
}
char *HttpRequest::getReferer(){
    return referer;
}
char *HttpRequest::getOrigin(){
    return origin;
}

REQUEST_METHOD HttpRequest::getMethod(){
   return method;
}