//
// Created by choune on 2/17/23.
//

#ifndef ARCADE_PONG_BALL_H
#define ARCADE_PONG_BALL_H

#include <stdbool.h>

struct Ball {
    int x;
    int y;
    int x_speed;
    int y_speed;
    int radius;
    bool is_alive;
    bool is_debug_mode;
    char* log_file_path;
};

struct Ball init_ball(int radius, bool debugMode, char* logFilePath);

int move_ball(struct Ball* ball);

#endif //ARCADE_PONG_BALL_H
