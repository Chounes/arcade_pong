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

    // Show debug message if debug mode is active
    if (res != 0) {
        printf("Error : logfile may be not accessible or does not exist\n");
        exit(1);
    }

    // Launch game in window mode
    log_all("Starting game in window mode\n", LOG_FILE_PATH);
    res = menu();
    if (res != 0) {
        log_all("Error : menu failed to start\n", LOG_FILE_PATH);
        exit(1);
    }

    return 0;
}

int menu() {
    char frapped_key = '0';
    int index = 0;
    WINDOW *menu_win;
    WINDOW *title_win;
    WINDOW *play_btn;
    WINDOW *setting_btn;
    WINDOW *exit_btn;
    WINDOW *credit_btn;

    // Initialize ncurses
    initscr();

    // Clear screen
    clear();

    // Disable input buffering
    cbreak();

    // Disable echo of typed characters
    noecho();
    menu_win = subwin(stdscr, LINES, COLS, 0, 0);
    set_title(title_win);

    // Enable keypad input
    keypad(stdscr, TRUE);
    while (1) {
        int res = menu_displayer(index, menu_win, title_win, play_btn, setting_btn, exit_btn, credit_btn);
        if (res != 0) {
            log_all("Error : menu failed to start\n", LOG_FILE_PATH);
            exit(1);
        }
        frapped_key = getch();
        switch (frapped_key) {
            case 119:
                if (index > 0) {
                    index--;
                } else {
                    index = 3;
                }
                break;
            case 3:
                if (index > 0) {
                    index--;
                } else {
                    index = 3;
                }
                break;
            case 115:
                if (index < 3) {
                    index++;
                } else {
                    index = 0;
                }
                break;
            case 2:
                if (index < 3) {
                    index++;
                } else {
                    index = 0;
                }
                break;
            case 10:
                if (index == EXIT_IDX) return 0;
            default:
                printf("Frapped key = %c\n", ('0' + frapped_key));
                printf("You chose an invalid option\n");

        }
    }
}


int
menu_displayer(int index, WINDOW *menu_win, WINDOW *title_win, WINDOW *play_btn, WINDOW *setting_btn, WINDOW *exit_btn,
               WINDOW *credit_btn) {
    logg("Display menu\n", LOG_FILE_PATH);
    set_play_btn(play_btn, index);
    set_setting_btn(setting_btn, index);
    set_exit_btn(exit_btn, index);
    set_credit_btn(credit_btn, index);

    wrefresh(menu_win);
    return 0;
}


i

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

void set_play_btn(WINDOW *play_btn, int index) {
    clear_play_btn(play_btn);
    play_btn = subwin(stdscr, 5, 30, (LINES / 5), (COLS / 2) - 15);
    box(play_btn, ACS_VLINE, ACS_HLINE);
    if (index == PLAY_IDX) {
        mvwprintw(play_btn, 2, (30 / 2) - 2, ">PLAY<");
    } else {
        mvwprintw(play_btn, 2, (30 / 2) - 2, "PLAY");
    }
    wrefresh(play_btn);
}

void clear_play_btn(WINDOW *play_btn) {
    play_btn = subwin(stdscr, 5, 30, (LINES / 5), (COLS / 2) - 15);
    werase(play_btn);
    wrefresh(play_btn);
}

void clear_setting_btn(WINDOW *setting_btn) {
    setting_btn = subwin(stdscr, 5, 30, (LINES / 5) * 1.5, (COLS / 2) - 15);
    werase(setting_btn);
    wrefresh(setting_btn);
}

void set_setting_btn(WINDOW *setting_btn, int index) {
    clear_setting_btn(setting_btn);
    setting_btn = subwin(stdscr, 5, 30, (LINES / 5) * 1.5, (COLS / 2) - 15);
    box(setting_btn, ACS_VLINE, ACS_HLINE);
    if (index == SETTING_IDX) {
        mvwprintw(setting_btn, 2, (30 / 2) - 4, ">SETTINGS<");
    } else {
        mvwprintw(setting_btn, 2, (30 / 2) - 4, "SETTINGS");
    }
    wrefresh(setting_btn);
}


void set_exit_btn(WINDOW *exit_btn, int index) {
    clear_exit_btn(exit_btn);
    exit_btn = subwin(stdscr, 5, 30, (LINES / 5) * 2.5, (COLS / 2) - 15);
    box(exit_btn, ACS_VLINE, ACS_HLINE);
    if (index == EXIT_IDX) {
        mvwprintw(exit_btn, 2, (30 / 2) - 2, ">EXIT<");
    } else {
        mvwprintw(exit_btn, 2, (30 / 2) - 2, "EXIT");
    }
    wrefresh(exit_btn);
}

void clear_exit_btn(WINDOW *exit_btn) {
    exit_btn = subwin(stdscr, 5, 30, (LINES / 5) * 2.5, (COLS / 2) - 15);
    werase(exit_btn);
    wrefresh(exit_btn);
}

void clear_credit_btn(WINDOW *credit_btn) {
    credit_btn = subwin(stdscr, 5, 30, (LINES / 5) * 2, (COLS / 2) - 15);
    werase(credit_btn);
    wrefresh(credit_btn);
}

void set_credit_btn(WINDOW *credit_btn, int index) {
    clear_credit_btn(credit_btn);
    credit_btn = subwin(stdscr, 5, 30, (LINES / 5) * 2, (COLS / 2) - 15);
    box(credit_btn, ACS_VLINE, ACS_HLINE);
    if (index == CREDIT_IDX) {
        mvwprintw(credit_btn, 2, (30 / 2) - 3, ">CREDITS<");
    } else {
        mvwprintw(credit_btn, 2, (30 / 2) - 3, "CREDITS");
    }
    wrefresh(credit_btn);
}
