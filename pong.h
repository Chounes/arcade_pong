#ifndef ARCADE_PONG_PONG_H
#define ARCADE_PONG_PONG_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


bool DEBUG = false;
char* LOG_FILE = "./pong.log";

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


void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect *rect);
int menuLoop(SDL_Window *window, SDL_Renderer *renderer );
void badArgumentsError();
void tooManyArgumentsError();
#endif //ARCADE_PONG_PONG_H
