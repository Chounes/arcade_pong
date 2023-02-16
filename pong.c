#include "src_logger/logger.c"
#include "pong.h"
#include "src_menu/menu.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONSOLE false
#define LOG_FILE_PATH "./services_log/pong.log"
//#define DEBUG true

int main(){
    int res = start_log(LOG_FILE_PATH);
    if(res != 0){
        printf("Error : logfile may be not accessible or does not exist\n");
        exit(1);
    }
    if(CONSOLE){
        logger("Starting game in console mode", LOG_FILE_PATH);
        printf("Starting game in console mode");
    }
    else{
        logger("Starting game in window mode\n", LOG_FILE_PATH);
        open_menu();
    }


    return 0;
}