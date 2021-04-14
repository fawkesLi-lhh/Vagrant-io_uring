#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>

#include "AssetManager.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager(){
   char path[1111] = "asset";
   ReadDir(path);
}

void AssetManager::ReadDir(char *path){
   DIR *dir; dirent *ptr;int len = strlen(path);
   if ((dir=opendir(path)) == NULL){
      perror("Open dir error...");
      exit(1);
   }
   while ((ptr=readdir(dir)) != NULL){
      if(ptr->d_name[0] == '.') continue;
      strcat(path,"/");
      strcat(path,ptr->d_name);
      if(ptr->d_type == 8) {
         struct stat file_stat;
         stat(path,&file_stat);
         int fd = open(path,O_RDONLY);
         char* data = (char *)mmap(0,file_stat.st_size,PROT_READ,MAP_PRIVATE,fd,0);
         int len = file_stat.st_size;
         mp[::std::string(path+5)] = {data,len};
      }
      if(ptr->d_type == 4) ReadDir(path);
      path[len] = '\0';
   }
   closedir(dir);
}

AssetManager* AssetManager::getInstance(){
   if(instance == nullptr)instance = new AssetManager();
   return instance;
}

File AssetManager::getFile(::std::string name){
   if(mp.find(name) == mp.end()) return { nullptr,0};
   return mp[name];
}