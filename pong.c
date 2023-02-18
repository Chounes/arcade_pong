#include "src_logger/logger.c"
#include "pong.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "src_ball/ball.c"

//#define DEBUG true

char *choices[] = {
        "PLAY",
        "SETTINGS",
        "CREDITS",
        "EXIT",
};

WINDOW *create_newwin(int height, int width, int starty, int startx);

void destroy_win(WINDOW *local_win);


int main(int argc, char *argv[]) {
    int res = start_log(LOG_FILE_PATH);
    // check as argument if we want to start in console mode
    bool CONSOLE = false;
    if (argc > 1) {
        if (strcmp(argv[1], "-console") == 0) {
            CONSOLE = true;
        }
    }
    if (res != 0) {
        printf("Error : logfile may be not accessible or does not exist\n");
        exit(1);
    }
    if (CONSOLE) {
        logger("Starting game in console mode", LOG_FILE_PATH);
        printf("%s", TITLE);
        res = console_menu();
    } else {
        logger("Starting game in window mode\n", LOG_FILE_PATH);
//        res = menu();
//        if (res != 0) {
//            logger("Error : menu failed to start\n", LOG_FILE_PATH);
//            exit(1);
//        }
    }
    return 0;
}


int console_menu() {
    printf("Choog one : \n");
    for (int i = 0; i < 4; i++) {
        printf("\t%d - %s\n", i, choices[i]);
    }
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 0:
            logger("Starting game", LOG_FILE_PATH);
            console_play();
            logger("Game ended", LOG_FILE_PATH);
            break;
        case 1:
            printf("You chose to change settings\n");
            break;
        case 2:
            printf("You chose to see credits\n");
            console_credits();
            break;
        case 3:
            printf("You chose to exit\n");
            break;
        default:
            printf("You chose an invalid option\n");
            break;
    }
    return 0;
}

int console_play() {
    struct Ball b = init_ball(5);
    bool running = true;
    while (running){
        move_ball(&b);
    }
    return 0;
}

int console_credits() {
    printf("Credits : \n");
    printf("Made by : \n");
    printf("%s\n", AUTHOR);
    return 0;
}