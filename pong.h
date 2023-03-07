#ifndef ARCADE_PONG_PONG_H
#define ARCADE_PONG_PONG_H

#include <stdbool.h>
#include <ncurses.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


#define DOWN 1
#define UP 2
#define LEFT 3
#define RIGHT 4


const char *AUTHOR= " ██████╗██╗  ██╗ ██████╗ ██╗   ██╗███╗   ██╗███████╗\n██╔════╝██║  ██║██╔═══██╗██║   ██║████╗  ██║██╔════╝\n██║     ███████║██║   ██║██║   ██║██╔██╗ ██║█████╗\n██║     ██╔══██║██║   ██║██║   ██║██║╚██╗██║██╔══╝\n╚██████╗██║  ██║╚██████╔╝╚██████╔╝██║ ╚████║███████╗\n ╚═════╝╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚══════╝\n";
const char *TITLE= "8888888b.   .d88888b.  888b    888  .d8888b.  \n888   Y88b d88P   Y88b 8888b   888 d88P  Y88b \n888    888 888     888 88888b  888 888    888 \n888   d88P 888     888 888Y88b 888 888        \n8888888P   888     888 888 Y88b888 888  88888 \n888        888     888 888  Y88888 888    888\n888        Y88b. .d88P 888   Y8888 Y88b  d88P \n888          Y88888P   888    Y888  Y8888P88 \n\n\n";
#define LOG_FILE_PATH "./services_log/pong.log"
const char *choices[] = {
        "PLAY",
        "SETTINGS",
        "CREDITS",
        "EXIT",
};
bool CONSOLE = false;
bool DEBUG = false;


int menu();
int console_menu();
int console_credits();
int console_play();
int console_settings();
int menu_displayer(int index, WINDOW *menu_win, WINDOW *title_win);
void set_title(WINDOW *title_win);
void clear_title(WINDOW *title_win);
void clear_menu(WINDOW *menu_win);
void set_play_btn(WINDOW *play_btn, int index);
void clear_play_btn(WINDOW *play_btn);


#endif //ARCADE_PONG_PONG_H
