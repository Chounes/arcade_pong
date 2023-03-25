#ifndef ARCADE_PONG_PONG_H
#define ARCADE_PONG_PONG_H

#include <stdbool.h>
#include <SDL2/SDL.h>


bool CONSOLE = false;
bool DEBUG = false;

SDL_Color WHITE = {255, 255, 255, 255};
SDL_Color BLACK = {0, 0, 0, 255};
SDL_Color RED = {255, 0, 0, 255};
SDL_Color GREEN = {0, 255, 0, 255};
SDL_Color BLUE = {0, 0, 255, 255};
SDL_Color CYAN = {0, 255, 255, 255};

struct WINDOW {
    SDL_Window *window;
    SDL_Renderer *renderer;
};


struct WINDOW* setupWindow(int width, int height);
int destroyWindow(struct WINDOW *window);
int setWindowColor(struct WINDOW* window, SDL_Color color);
int setStartBtn(struct WINDOW* window);
#endif //ARCADE_PONG_PONG_H
