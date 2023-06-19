//
// Created by Ning on 2023/6/8.
//
#include "common.h"
#ifdef _MOVE_2
#include <SDL.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define RECT_SIZE 32
#define MOVE_INTERVAL 1000

typedef struct {
    int x;
    int y;
} Point;

void move_rect(Point* position, int dx, int dy) {
    // 移动矩形
    position->x += dx * RECT_SIZE;
    position->y += dy * RECT_SIZE;

    // 限制矩形在屏幕内移动
    if (position->x < 0) {
        position->x = 0;
    } else if (position->x > SCREEN_WIDTH - RECT_SIZE) {
        position->x = SCREEN_WIDTH - RECT_SIZE;
    }
    if (position->y < 0) {
        position->y = 0;
    } else if (position->y > SCREEN_HEIGHT - RECT_SIZE) {
        position->y = SCREEN_HEIGHT - RECT_SIZE;
    }
}

Uint32 move_timer_callback(Uint32 interval, void* param) {
    // 转换参数
    Point* position = (Point*) param;

    // 随机移动矩形
    int dx = rand() % 3 - 1;
    int dy = rand() % 3 - 1;
    move_rect(position, dx, dy);

    // 返回下一次定时器的间隔
    return interval;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_TimerID timer = 0;

    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL初始化失败: %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    window = SDL_CreateWindow("SDL定时器移动", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("窗口创建失败: %s\n", SDL_GetError());
        return 1;
    }

    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("渲染器创建失败: %s\n", SDL_GetError());
        return 1;
    }

    // 初始化矩形位置
    Point position = { SCREEN_WIDTH / 2 - RECT_SIZE / 2, SCREEN_HEIGHT / 2 - RECT_SIZE / 2 };

    // 创建定时器
    timer = SDL_AddTimer(MOVE_INTERVAL, move_timer_callback, &position);

    // 游戏循环
    SDL_Event event;
    while (true) {
        // 处理事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto end;
            }
        }

        // 清空渲染器
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 绘制矩形
        SDL_Rect rect = { position.x, position.y, RECT_SIZE, RECT_SIZE };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        // 更新屏幕
        SDL_RenderPresent(renderer);
    }

end:
    // 移除定时器
    SDL_RemoveTimer(timer);

    // 清理资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
#endif