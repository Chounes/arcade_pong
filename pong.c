#include "src_logger/logger.c"
#include "pong.h"
#include "src_sound/sound.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "src_ball/ball.c"


int main(int argc, char *argv[]) {
    int res = start_log(LOG_FILE_PATH);
    int status = EXIT_FAILURE;

    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0) {
            CONSOLE = true;
        } else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0) {
            DEBUG = true;
            log_all("Debug mod active", LOG_FILE_PATH);
        }
    }

    if (res != 0) {
        printf("Error : logfile may be not accessible or does not exist");
        return status;
    }

    reset_log(LOG_FILE_PATH);
    log_all("Starting game in window mode", LOG_FILE_PATH);


    // Init SDL
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        log_all("Error : SDL_Init failed", LOG_FILE_PATH);
        log_all(SDL_GetError(), LOG_FILE_PATH);
        status = EXIT_FAILURE;
        goto Quit;
    }

    struct WINDOW *window = setupWindow(800, 800);

    SDL_Delay(3000);

    setStartBtn(window);

    SDL_Delay(3000);
    destroyWindow(window);


    status = EXIT_SUCCESS;
    Quit:
    SDL_Quit();
    exit(status);
}


struct WINDOW *setupWindow(int width, int height) {
    struct WINDOW *window = malloc(sizeof(struct WINDOW));
    window->window = NULL;
    window->renderer = NULL;
    window->window = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width, height, SDL_WINDOW_SHOWN);
    if (NULL == window) {
        log_all("Error : SDL_CreateWindow failed", LOG_FILE_PATH);
        log_all(SDL_GetError(), LOG_FILE_PATH);
        goto Quit;
    }
    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == window->renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }

    setWindowColor(window, BLACK);

    return window;
    Quit:
    destroyWindow(window);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

int destroyWindow(struct WINDOW *window) {
    if (NULL != window->renderer) {
        SDL_DestroyRenderer(window->renderer);
    }
    if (NULL != window->window) {
        SDL_DestroyWindow(window->window);
    }
    free(window);
    return 0;
}

int setWindowColor(struct WINDOW* window, SDL_Color color) {
    if (SDL_SetRenderDrawColor(window->renderer, color.r, color.g, color.b, color.a) != 0) {
        log_all("Error : SDL_SetRenderDrawColor failed", LOG_FILE_PATH);
        log_all(SDL_GetError(), LOG_FILE_PATH);
        destroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);
    return 0;
}

int setStartBtn(struct WINDOW* window) {
    // Get the window size
    int winWidth, winHeight;
    SDL_GetWindowSize(window->window, &winWidth, &winHeight);
    SDL_Rect rect;
    rect.x = winWidth / 2 - 50;
    rect.y = winHeight / 3  + winHeight/6 - 25;
    rect.w = 100;
    rect.h = 50;
    SDL_SetRenderDrawColor(window->renderer, CYAN.r, CYAN.g, CYAN.b, CYAN.a);
    SDL_RenderDrawRects(window->renderer, &rect,4);
    SDL_RenderPresent(window->renderer);
    return 0;
}

