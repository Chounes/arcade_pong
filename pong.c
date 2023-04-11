#include "src_logger/logger.c"
#include "pong.h"
#include "src_sound/sound.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "src_ball/ball.c"
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH (640*1.5)
#define SCREEN_HEIGHT (480*1.5)


int main(int argc, char *argv[]) {

    if (argc == 2) {
        if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0) {
            DEBUG = true;
        } else {
            badArgumentsError();
        }
    } else if (argc == 3) {
        if (strcmp(argv[1], "--dir") == 0) {
            LOG_FILE = argv[2];
        } else {
            badArgumentsError();
        }
    } else if (argc == 4) {
        if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0) {
            DEBUG = true;
            if (strcmp(argv[2], "--dir") == 0) {
                LOG_FILE = argv[3];
            } else {
                badArgumentsError();
            }
        } else {
            badArgumentsError();
        }
    } else if (argc > 4) {
        tooManyArgumentsError();
    }

    initLog(LOG_FILE);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("PONG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    menuLoop(window, renderer);

    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect *rect) {
    char message[100];
    sprintf(message, "renderText for : %s", text);
    loggerInfo(message, LOG_FILE);
    if(renderer == NULL) {
        loggerDebug("Error: \"renderer\" value is NULL", LOG_FILE, DEBUG);
        exit(EXIT_FAILURE);
    }
    if (font == NULL) {
        loggerDebug("Error: \"font\" value is NULL", LOG_FILE, DEBUG);
        exit(EXIT_FAILURE);
    }
    if (text == NULL) {
        loggerDebug("Warning: \"text\" value is NULL", LOG_FILE, DEBUG);
    }
    if (rect == NULL) {
        loggerDebug("Error: \"rect\" value is NULL", LOG_FILE, DEBUG);
        exit(EXIT_FAILURE);
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, WHITE);
    if (surface == NULL) {
        loggerDebug("Error: \"TTF_RenderText_Solid\" return NULL value", LOG_FILE, DEBUG);
        exit(EXIT_FAILURE);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == NULL) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return;
    }
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}

int menuLoop(SDL_Window *window, SDL_Renderer *renderer) {
    TTF_Font *font = TTF_OpenFont("./fonts/RussoOne-Regular.ttf", 20);
    SDL_Rect playButtonRect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 7 - 25, 100, 50};
    SDL_Rect settingButtonRect = {SCREEN_WIDTH / 2 - 50, (SCREEN_HEIGHT / 7) * 3 - 25, 100, 50};
    SDL_Rect quitButtonRect = {SCREEN_WIDTH / 2 - 50, (SCREEN_HEIGHT / 7) * 5 - 25, 100, 50};
    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if (mouseX >= playButtonRect.x && mouseX <= playButtonRect.x + playButtonRect.w &&
                    mouseY >= playButtonRect.y && mouseY <= playButtonRect.y + playButtonRect.h) {
                    loggerDebug("Play Button Clicked", LOG_FILE, DEBUG);
                }
                if (mouseX >= settingButtonRect.x && mouseX <= settingButtonRect.x + settingButtonRect.w &&
                    mouseY >= settingButtonRect.y && mouseY <= settingButtonRect.y + settingButtonRect.h) {
                    loggerDebug("Setting Button Clicked", LOG_FILE, DEBUG);
                }
                if (mouseX >= quitButtonRect.x && mouseX <= quitButtonRect.x + quitButtonRect.w &&
                    mouseY >= quitButtonRect.y && mouseY <= quitButtonRect.y + quitButtonRect.h) {
                    loggerDebug("Quit Button Clicked", LOG_FILE, DEBUG);
                    running = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &playButtonRect);
        SDL_RenderFillRect(renderer, &settingButtonRect);
        SDL_RenderFillRect(renderer, &quitButtonRect);

        renderText(renderer, font, "PLAY\0", &playButtonRect);
        renderText(renderer, font, "SETTING\0", &settingButtonRect);
        renderText(renderer, font, "QUIT\0", &quitButtonRect);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    return 0;
}

void badArgumentsError() {
    printf("Error : bad arguments.\n");
    printf("Usage : pong [-d | --debug] [--dir <path>]\n");
    exit(1);
}

void tooManyArgumentsError() {
    printf("Error : to many arguments.\n");
    printf("Usage : pong [-d | --debug] [--dir <path>]\n");
    exit(1);
}