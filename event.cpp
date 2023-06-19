// 实现事件响应
// Created by Ning on 2022/8/13.
//

#include <SDL.h>
#include <iostream>
#include "event.h"
#include "texture.h"

void on_mouse_down(SDL_Renderer *sr, SDL_Texture *st) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    std::cout << "mouse on: " << x << ", " << y << std::endl;

    if (st == NULL) {
        std::cerr << "mouse icon texture load fail, icon not show" << std::endl;
        return;
    }

    if (blit(sr, st, x, y, 1) < 0) {
        std::cerr << "mouse icon load fail" << std::endl;
    }
}

void on_mouse_move(SDL_Renderer *sr, SDL_Texture *st) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (st == NULL) {
        std::cerr << "mouse icon texture load fail, icon not show" << std::endl;
        return;
    }

    if (blit(sr, st, x, y, 1) < 0) {
        std::cerr << "mouse icon motion render fail" << std::endl;
        return;
    }
}