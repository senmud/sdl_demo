//
// Created by Ning on 2023/6/8.
//

#include "common.h"
#ifdef _MOVE_1

#include <SDL.h>
#include <random>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define RECT_SIZE 32

typedef struct {
    int x;
    int y;
} Point;

static std::default_random_engine e;
static std::uniform_int_distribution<unsigned> id(0, 1000);

void move_rect(Point* position) {
    // 随机移动矩形

    int dx = id(e) % 3 - 1;
    int dy = id(e) % 3 - 1;
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

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL初始化失败: %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    window = SDL_CreateWindow("SDL随机移动", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // 初始化随机数生成器
    //srand(time(nullptr));
    e.seed(time(nullptr));

    // 初始化矩形位置
    Point position = { SCREEN_WIDTH / 2 - RECT_SIZE / 2, SCREEN_HEIGHT / 2 - RECT_SIZE / 2 };

    // 游戏循环
    SDL_Event event;
    while (true) {
        // 处理事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto end;
            }
        }

        // 移动矩形
        move_rect(&position);

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
    //清理资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
#endif