//
// Created by Ning on 2023/4/26.
//
#include <SDL.h>
#include <cstdio>
#include "common.h"

// 定义窗口大小
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#ifdef _DEMO1_
int main(int argc, char* args[]) {
    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    SDL_Window* window = SDL_CreateWindow("SDL Game Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 加载图片
    SDL_Surface* image = SDL_LoadBMP("/Users/ning/Downloads/sample_640×426.bmp");
    if (image == nullptr) {
        printf("Image could not be loaded! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 创建纹理
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == nullptr) {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 释放图片
    SDL_FreeSurface(image);

    // 设置渲染颜色
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // 清空屏幕
    SDL_RenderClear(renderer);

    // 渲染纹理
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    // 更新屏幕
    SDL_RenderPresent(renderer);

    // 等待退出事件
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // 销毁纹理、窗口和渲染器
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // 退出SDL
    SDL_Quit();

    return 0;
}
#endif
