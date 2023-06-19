// 加载材质
// Created by Ning on 2022/8/13.
//

#ifndef SDL_DEMO_TEXTURE_H
#define SDL_DEMO_TEXTURE_H

#include <SDL.h>
#include <string>

struct texture_str {
    SDL_Texture * texture;
    SDL_Surface * surface;

    texture_str();
    void free();
    bool isValid() const;
};

SDL_Texture* loadTexture(std::string path, SDL_Renderer *r);

texture_str loadTextureWithSurface(const std::string &path, SDL_Renderer *r);

void releaseTexture(SDL_Texture *st);

int blit(SDL_Renderer *sr, SDL_Texture *st, int x, int y, int center);

#endif //SDL_DEMO_TEXTURE_H
