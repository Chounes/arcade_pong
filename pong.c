#include "src_logger/logger.c"
#include "pong.h"
#include "src_sound/sound.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "src_ball/ball.c"


int sound_pid = 0;


int main(int argc, char *argv[]) {
    int res = start_log(LOG_FILE_PATH);
    // check as argument if we want to start in console mode
    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0) {
            CONSOLE = true;
        } else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0) {
            DEBUG = true;
            log_all("Debug mod active\n", LOG_FILE_PATH);
        }
    }
    if (argc > 2) {
        if (strcmp(argv[2], "-c") == 0) {
            CONSOLE = true;
        } else if (strcmp(argv[2], "-d") == 0 || strcmp(argv[2], "--debug") == 0) {
            DEBUG = true;
            log_all("Debug mod active\n", LOG_FILE_PATH);
        }
    }
    if (res != 0) {
        printf("Error : logfile may be not accessible or does not exist\n");
        exit(1);
    }
    if (CONSOLE) {
        log_all("Starting game in console mode", LOG_FILE_PATH);
        printf(ANSI_COLOR_GREEN "%s", TITLE);
        printf(ANSI_COLOR_RESET "\n");
        res = console_menu();
    } else {
        log_all("Starting game in window mode\n", LOG_FILE_PATH);
        res = menu();
        if (res != 0) {
            log_all("Error : menu failed to start\n", LOG_FILE_PATH);
            exit(1);
        }
    }

//    if (sound_pid != 0) {
//        kill(sound_pid, SIGKILL);
//    }
    return 0;
}

int menu() {
    char frapped_key = '0';
    int index = 0;
    WINDOW *menu_win;
    WINDOW *title_win;
    // create windows (name, size, position, parent window
    initscr();
    menu_win = subwin(stdscr, LINES, COLS, 0, 0);
    set_title(title_win);
    while (1) {
        int res = menu_displayer(index, menu_win, title_win);
        if (res != 0) {
            log_all("Error : menu failed to start\n", LOG_FILE_PATH);
            exit(1);
        }

        scanf("%c", &frapped_key);
        if(frapped_key == 'w'){
//            if (index > 0) {
//                index--;
//            } else {
//                index = 3;
//            }
            set_title(title_win);
        }
        else if(frapped_key == 's'){
//            if (index < 3) {
//                index++;
//            } else {
//                index = 0;
//            }
            clear_title(title_win);
        }
        else if(frapped_key == 'q'){
            break;
        }
    }
//    free(menu_win);
//    free(title_win);
    endwin();
    printf("Bye bye\n");
    return 0;
}

void clear_menu(WINDOW *menu_win) {
    menu_win = subwin(stdscr, LINES, COLS, 0, 0);
    werase(menu_win);
    wrefresh(menu_win);
}

void clear_title(WINDOW *title_win) {
    title_win = subwin(stdscr, 10, 50, 1, (COLS / 2) - 25);
    werase(title_win);
    wrefresh(title_win);
}

void set_title(WINDOW *title_win) {
    title_win = subwin(stdscr, 10, 50, 1, (COLS / 2) - 25);
    mvwprintw(title_win, 1, 2, "8888888b.   .d88888b.  888b    888  .d8888b.  ");
    mvwprintw(title_win, 2, 2, "888   Y88b d88P   Y88b 8888b   888 d88P  Y88b ");
    mvwprintw(title_win, 3, 2, "888    888 888     888 88888b  888 888    888 ");
    mvwprintw(title_win, 4, 2, "888   d88P 888     888 888Y88b 888 888        ");
    mvwprintw(title_win, 5, 2, "8888888P   888     888 888 Y88b888 888  88888 ");
    mvwprintw(title_win, 6, 2, "888        888     888 888  Y88888 888    888 ");
    mvwprintw(title_win, 7, 2, "888        Y88b. .d88P 888   Y8888 Y88b  d88P ");
    mvwprintw(title_win, 8, 2, "888          Y88888P   888    Y888  Y8888P88  ");
    wrefresh(title_win);
}

 void set_play_btn(WINDOW *play_btn,  int index) {
     play_btn = subwin(stdscr, 5, 30, (LINES / 5), (COLS / 2) - 15);
     box(play_btn, ACS_VLINE, ACS_HLINE);
     if(index == 0){
         mvwprintw(play_btn, 2, (30 / 2) - 2, ">PLAY<");
     }
     else{
         mvwprintw(play_btn, 2, (30 / 2) - 2, "PLAY");
     }
     wrefresh(play_btn);
 }

 void clear_play_btn(WINDOW *play_btn) {
     play_btn = subwin(stdscr, 5, 30, (LINES / 5), (COLS / 2) - 15);
     werase(play_btn);
     wrefresh(play_btn);
 }

int menu_displayer(int index, WINDOW *menu_win, WINDOW *title_win) {
    logg("Display menu\n", LOG_FILE_PATH);
    wrefresh(menu_win);
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
            log_all("Starting game", LOG_FILE_PATH);
            console_play();
            log_all("Game ended", LOG_FILE_PATH);
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