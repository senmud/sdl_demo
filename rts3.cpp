//
// Created by Ning on 2023/4/28.
//
#include <SDL.h>
#include "common.h"
#include "texture.h"

#ifdef _RTS_GAME3_

static const int win_width = 1024, win_height = 768, sprite_w = 32, sprite_h = 32;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Sprite Movement", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    //SDL_Surface* spriteSurface = SDL_LoadBMP("sprite.bmp");

    //SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);

    //SDL_Texture *texture = loadTexture("/Users/ning/Pictures/spirit2.jpeg", renderer);
    texture_str trs = loadTextureWithSurface("/Users/ning/Pictures/spirit2.jpeg", renderer);

    SDL_Rect spriteRect;
    spriteRect.x = 0;
    spriteRect.y = 0;
    spriteRect.w = sprite_w;
    spriteRect.h = sprite_h;

    int quit = 0;
    SDL_Event event;
    static const int step = 1;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        const Uint8* state = SDL_GetKeyboardState(nullptr);

        if (state[SDL_SCANCODE_LEFT]) {
            spriteRect.x -= spriteRect.x < step ? spriteRect.x : step;
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            spriteRect.x += spriteRect.x > win_width - step - sprite_w ? win_width - spriteRect.x - sprite_w : step;
        }

        if (state[SDL_SCANCODE_UP]) {
            spriteRect.y -= spriteRect.y < step ? spriteRect.y : step;
        }

        if (state[SDL_SCANCODE_DOWN]) {
            spriteRect.y += spriteRect.y > win_height - step -sprite_h ? win_height - spriteRect.y -sprite_h : step;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, trs.texture, nullptr, &spriteRect);
        SDL_RenderPresent(renderer);
    }

    trs.free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
#endif