// 加载材质实现
// Created by Ning on 2022/8/13.
//

#include <SDL_image.h>
#include <SDL_rect.h>
#include <iostream>
#include "texture.h"

texture_str::texture_str() {
    texture = nullptr;
    surface = nullptr;
}

void texture_str::free() {
    if (this->surface != nullptr) {
        SDL_FreeSurface(this->surface);
    }
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
    }
    this->surface = nullptr;
    this->texture = nullptr;
}

bool texture_str::isValid() const {
    return this->surface != nullptr;
}

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer *r) {
    SDL_Texture *pt = nullptr;
    SDL_Surface *sr = IMG_Load(path.c_str());
    if (sr == nullptr) {
        std::cerr << "img load fail: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    pt = SDL_CreateTextureFromSurface(r, sr);
    SDL_FreeSurface(sr);

    return pt;
}

texture_str loadTextureWithSurface(const std::string &path, SDL_Renderer *r) {
    texture_str data;
    data.surface = IMG_Load(path.c_str());
    if (data.surface == nullptr) {
        std::cerr << "img load fail: " << SDL_GetError() << std::endl;
        data.free();
        return data;
    }

    data.texture = SDL_CreateTextureFromSurface(r, data.surface);
    return data;
}

void releaseTexture(SDL_Texture *st) {
    if (st == nullptr) {
        return;
    }

    SDL_DestroyTexture(st);
}

int blit(SDL_Renderer *sr, SDL_Texture *st, int x, int y, int center) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    if (SDL_QueryTexture(st, nullptr, nullptr, &dest.w, &dest.h) != 0) {
        return -1;
    }

    if (center) {
        dest.x -= dest.w / 2;
        dest.y -= dest.h / 2;
    }

    SDL_RenderClear(sr);
    SDL_RenderCopy(sr, st, nullptr, &dest);
    SDL_RenderPresent(sr);
    return 0;
}