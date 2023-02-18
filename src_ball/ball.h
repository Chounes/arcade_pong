//
// Created by choune on 2/17/23.
//

#ifndef ARCADE_PONG_BALL_H
#define ARCADE_PONG_BALL_H
#define LOG_FILE_PATH "./services_log/pong.log"

struct Ball {
    int x;
    int y;
    int x_speed;
    int y_speed;
    int radius;
};

struct Ball init_ball(int radius);

int move_ball(struct Ball* ball);

#endif //ARCADE_PONG_BALL_H
