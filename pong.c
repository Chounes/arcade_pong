#include "src_logger/logger.c"
#include "pong.h"
#include "src_sound/sound.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "src_ball/ball.c"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ioctl.h>


int sound_pid = 0;


int main(int argc, char *argv[]) {
    int res = start_log(LOG_FILE_PATH);
    // check as argument if we want to start in console mode
    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0) {
            CONSOLE = true;
        }
        else if (strcmp(argv[1], "-d") == 0) {
            DEBUG = true;
            logger("Debug mod active\n", LOG_FILE_PATH);
        }
    }
    if(argc > 2){
        if (strcmp(argv[2], "-c") == 0) {
            CONSOLE = true;
        }
        else if (strcmp(argv[2], "-d") == 0) {
            DEBUG = true;
            logger("Debug mod active\n", LOG_FILE_PATH);
        }
    }
    if (res != 0) {
        printf("Error : logfile may be not accessible or does not exist\n");
        exit(1);
    }
    if (CONSOLE) {
        logger("Starting game in console mode", LOG_FILE_PATH);
        printf(ANSI_COLOR_GREEN "%s", TITLE);
        printf(ANSI_COLOR_RESET "\n");
        res = console_menu();
    } else {
        logger("Starting game in window mode\n", LOG_FILE_PATH);
        res = menu();
//        if (res != 0) {
//            logger("Error : menu failed to start\n", LOG_FILE_PATH);
//            exit(1);
//        }
    }

//    if (sound_pid != 0) {
//        kill(sound_pid, SIGKILL);
//    }
    return 0;
}

int menu(){
    logger("Display menu\n", LOG_FILE_PATH);
    WINDOW *menu_win;
    WINDOW *title_win;
    WINDOW *play_btn;
    WINDOW *settings_btn;
    WINDOW *credits_btn;
    WINDOW *exit_btn;
    WINDOW *debug_win;


    initscr();
    // create windows (name, size, position, parent window
    menu_win= subwin(stdscr, LINES, COLS, 0, 0);
    title_win= subwin(stdscr, 10, 50, 1, (COLS/2)-25);
    play_btn= subwin(stdscr, 5, 30, (LINES/5), (COLS/2)-15);
    settings_btn= subwin(stdscr, 5, 30, (LINES/5)*1.5, (COLS/2)-15);
    credits_btn= subwin(stdscr, 5, 30, (LINES/5)*2, (COLS/2)-15);
    exit_btn= subwin(stdscr, 5, 30, (LINES/5)*2.5, (COLS/2)-15);

    if(DEBUG) {
        debug_win = subwin(stdscr, 10, 30, 1, COLS-31);
        box(debug_win, ACS_VLINE, ACS_HLINE);
        mvwprintw(debug_win, 1, 1, "Start debug");
    }

    // Create border
    box(menu_win, ACS_VLINE, ACS_HLINE);
    box(play_btn, ACS_VLINE, ACS_HLINE);
    box(settings_btn, ACS_VLINE, ACS_HLINE);
    box(credits_btn, ACS_VLINE, ACS_HLINE);
    box(exit_btn, ACS_VLINE, ACS_HLINE);

    mvwprintw(play_btn, 2, (30/2)-2, "PLAY");
    mvwprintw(settings_btn, 2, (30/2)-4, "SETTINGS");
    mvwprintw(credits_btn, 2, (30/2)-4, "CREDITS");
    mvwprintw(exit_btn, 2, (30/2)-2, "EXIT");

    mvwprintw(title_win, 1, 2, "8888888b.   .d88888b.  888b    888  .d8888b.  ");
    mvwprintw(title_win, 2, 2, "888   Y88b d88P   Y88b 8888b   888 d88P  Y88b ");
    mvwprintw(title_win, 3, 2, "888    888 888     888 88888b  888 888    888 ");
    mvwprintw(title_win, 4, 2, "888   d88P 888     888 888Y88b 888 888        ");
    mvwprintw(title_win, 5, 2, "8888888P   888     888 888 Y88b888 888  88888 ");
    mvwprintw(title_win, 6, 2, "888        888     888 888  Y88888 888    888 ");
    mvwprintw(title_win, 7, 2, "888        Y88b. .d88P 888   Y8888 Y88b  d88P ");
    mvwprintw(title_win, 8, 2, "888          Y88888P   888    Y888  Y8888P88  ");


    wrefresh(menu_win);
    wrefresh(title_win);
    wrefresh(play_btn);
    wrefresh(settings_btn);
    wrefresh(credits_btn);
    wrefresh(exit_btn);
    if(DEBUG) wrefresh(debug_win);

    bool menu = true;
    while(menu){
        int res = getch();
        if(DEBUG) mvwprintw(debug_win, 1, 1, "Getch value : %d", res);
        switch(res){
            case KEY_UP:
                clear();
                if(DEBUG) mvwprintw(debug_win, 1, 1, "UP");
                break;
            case KEY_DOWN:
                clear();
                if(DEBUG) mvwprintw(debug_win, 1, 1,"DOWN");
                break;
            case KEY_F(9):
                menu = false;
            default:
                break;
        }
        refresh();
        if(DEBUG) wrefresh(debug_win);
    }
    endwin();

    free(menu_win);
    free(title_win);
    free(play_btn);
    free(settings_btn);
    free(credits_btn);
    free(exit_btn);
    if(DEBUG) free(debug_win);

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
            console_settings();
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
    for (int i = 0; i < 100; i++) {
        move_ball(&b);
    }
    return 0;
}

int console_credits() {
    printf("Credits : \n");
    printf("Made by : \n\n\n");
    printf(ANSI_COLOR_RED "%s\n", AUTHOR);
    printf(ANSI_COLOR_RESET "\n");
    return 0;
}

int console_settings() {
    printf("Settings : \n");
    printf("Choose one : \n");
//    printf("\t1 - Change difficulty\n");
    printf("\t2 - test sound\n");
//    printf("\t3 - Change controls\n");
//    printf("\t4 - Change color\n");
//    printf("\t5 - Change background\n");
//    printf("\t6 - Change ball\n");
//    printf("\t7 - Change paddle\n");

    int choice;
    scanf("%d", &choice);
    switch (choice) {
//        case 1:
//            printf("You chose to change difficulty\n");
//            break;
        case 2:
            printf("You chose to test sound\n");
//            sound_pid = fork();
//            if (sound_pid == 0) play_main_music();
//            printf("Sound should be playing his pid = %d\n", sound_pid);
//            sleep(10);
            break;
//        case 3:
//            printf("You chose to change controls\n");
//            break;
//        case 4:
//            printf("You chose to change color\n");
//            break;
//        case 5:
//            printf("You chose to change background\n");
//            break;
//        case 6:
//            printf("You chose to change ball\n");
//            break;
//        case 7:
//            printf("You chose to change paddle\n");
//            break;
        default:
            printf("You chose an invalid option\n");
            break;
    }

    return 0;
}