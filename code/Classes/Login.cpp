#include "Login.h"

#include <cstring>

bool Login::doPost(HttpRequest &req,HttpResponse &resp){
   printf("%s %s\n",req.getParameter("name"),req.getParameter("passward"));
   MysqlRAII sql;
   char buffer[555];
   sprintf(buffer,"SELECT name,passwd,nick FROM user where name='%s'",req.getParameter("name"));
   if (mysql_query(sql.sql, buffer)) {
      printf("sql error\n");
      return true;
   }
   MYSQL_RES *result = mysql_store_result(sql.sql);
   int num_fields = mysql_num_fields(result);
   MYSQL_FIELD *fields = mysql_fetch_fields(result);
   if (MYSQL_ROW row = mysql_fetch_row(result)) {
      if(strcmp(row[1],req.getParameter("passward")) == 0)
         sprintf(buffer,"{\n\"name\":\"%s\"\n}",row[2]);
      else
         sprintf(buffer,"{\n\"name\":\"passwd error\"\n}");   
   }
   else sprintf(buffer,"{\n\"name\":\"name error\"\n}");   
   
   resp.updateData(buffer);
   mysql_free_result(result);

   return true;
}
