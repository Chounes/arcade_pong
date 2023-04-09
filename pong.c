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

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect *rect)
{

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, WHITE);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("SDL Button", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("font.ttf", 24);
    SDL_Rect playButtonRect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 7 - 25, 100, 50};
    SDL_Rect settingButtonRect = {SCREEN_WIDTH / 2 - 50, (SCREEN_HEIGHT / 7)*3 - 25, 100, 50};
    SDL_Rect quitButtonRect = {SCREEN_WIDTH / 2 - 50, (SCREEN_HEIGHT / 7)*5 - 25, 100, 50};
    SDL_Event event;
    int running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if (mouseX >= playButtonRect.x && mouseX <= playButtonRect.x + playButtonRect.w && mouseY >= playButtonRect.y && mouseY <= playButtonRect.y + playButtonRect.h)
                {
                    printf("Play!\n");
                }
                if (mouseX >= settingButtonRect.x && mouseX <= settingButtonRect.x + settingButtonRect.w && mouseY >= settingButtonRect.y && mouseY <= settingButtonRect.y + settingButtonRect.h)
                {
                    printf("Setting!\n");
                }
                if (mouseX >= quitButtonRect.x && mouseX <= quitButtonRect.x + quitButtonRect.w && mouseY >= quitButtonRect.y && mouseY <= quitButtonRect.y + quitButtonRect.h)
                {
                    printf("Quit!\n");
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

        renderText(renderer, font, "PLAY", &playButtonRect);
        renderText(renderer, font, "SETTING", &settingButtonRect);
        renderText(renderer, font, "QUIT", &quitButtonRect);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
