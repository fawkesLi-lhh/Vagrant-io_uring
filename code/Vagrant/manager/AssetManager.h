#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include <string>
#include <map>

struct File {
   char *data;
   int len;
};

class AssetManager {
public:
   static AssetManager* getInstance();
   File getFile(::std::string);
private:
   void ReadDir(char * path);
   AssetManager();
   ::std::map<::std::string,File> mp;
   static AssetManager* instance;
};




#endif
