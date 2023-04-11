//
// Created by choune on 2/17/23.
//
#include <sys/ioctl.h>
#include "ball.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../src_logger/logger.h"


struct Ball init_ball(int radius, bool debugMode, char* logFilePath) {
    struct Ball ball;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    ball.x = w.ws_col / 2;

    ball.y = w.ws_row / 2;

    ball.x_speed = 1;

    ball.y_speed = 1;

    ball.radius = radius;

    ball.is_alive = true;

    ball.is_debug_mode = debugMode;

    ball.log_file_path = logFilePath;

    loggerDebug("Ball initialized", ball.log_file_path, ball.is_debug_mode);
    char message[100];
    sprintf(message, "Ball position: x=%d, y=%d", ball.x, ball.y);
    loggerDebug(message, ball.log_file_path, ball.is_debug_mode);
    sprintf(message, "win size : x=%d, y=%d", w.ws_col, w.ws_row);
    loggerDebug(message, ball.log_file_path, ball.is_debug_mode);

    return ball;

}

int move_ball(struct Ball* ball) {

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    char message[100];

    ball->x += ball->x_speed;

    ball->y += ball->y_speed;
    srand( time( NULL ) );

    if (ball->x + ball->radius >= w.ws_col || ball->x - ball->radius <= 0) {
        //generate random number between 7 and 5
        int random = rand() % 2 + 1;
        ball->x_speed = (ball->x_speed > 0) ? random : -random;
        ball->x_speed *= -1;
        loggerDebug("Ball hit the wall", ball->log_file_path, ball->is_debug_mode);
    }
    if(ball->y + ball->radius >= w.ws_row || ball->y - ball->radius <= 0) {
        //generate random number between 1 and 3
        int random = rand() % 2 + 1;
        ball->y_speed = (ball->y_speed > 0) ? random : -random;
        ball->y_speed *= -1;
        loggerDebug("Ball hit the wall", ball->log_file_path, ball->is_debug_mode);
    }
    sprintf(message, "Ball position: x=%d, y=%d", ball->x, ball->y);
    loggerDebug(message, ball->log_file_path, ball->is_debug_mode);
    return 0;

}
