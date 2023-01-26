#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include <time.h>
#include <string.h>
#include <dirent.h>


#define STR_SIZE 32



int main(){
    return start_log("pong", "./");
}


// Create logfile for current launch
int start_log(char* file_name, char* folder_path){
   if(STR_SIZE <= strlen(file_name)+16){
       printf("Error : logfile name length must be under 23 charcaters");
       exit(1);
   }
   DIR* dir = opendir(folder_path);
   if (dir) {
       closedir(dir);
    } 
   else{
      printf("Error : directory may be not accessible or does not exist");
      exit(1);
   }
    
   time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   char title[STR_SIZE];
   sprintf(title, "%d%d%d_%d%d%d_%s",tm.tm_mday, tm.tm_mon,tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec, file_name);
   printf("test %s", title);
   return 0;
}
