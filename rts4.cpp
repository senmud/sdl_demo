//
// Created by Ning on 2023/6/8.
//
#include "common.h"

#ifdef _RTS_GAME4_1
#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TILE_SIZE 32

#define MOVE_INTERVAL 30

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point position;
    int health;
} Unit;

typedef struct {
    int tiles[SCREEN_WIDTH / TILE_SIZE][SCREEN_HEIGHT / TILE_SIZE];
    Unit units[10];
    int num_units;
} Map;

void draw_map(SDL_Renderer* renderer, Map* map) {
    // 绘制地图
    for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE; x++) {
        for (int y = 0; y < SCREEN_HEIGHT / TILE_SIZE; y++) {
            SDL_Rect rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            if (map->tiles[x][y] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // 绘制单位
    for (int i = 0; i < map->num_units; i++) {
        SDL_Rect rect = { map->units[i].position.x, map->units[i].position.y, TILE_SIZE, TILE_SIZE };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void move_rect(Point* position, int dx, int dy) {
    // 移动矩形
    position->x += dx * TILE_SIZE;
    position->y += dy * TILE_SIZE;

    // 限制矩形在屏幕内移动
    if (position->x < 0) {
        position->x = 0;
    } else if (position->x > SCREEN_WIDTH - TILE_SIZE) {
        position->x = SCREEN_WIDTH - TILE_SIZE;
    }
    if (position->y < 0) {
        position->y = 0;
    } else if (position->y > SCREEN_HEIGHT - TILE_SIZE) {
        position->y = SCREEN_HEIGHT - TILE_SIZE;
    }
}

Uint32 move_timer_callback(Uint32 interval, void* param) {
    // 转换参数
    Map* map = (Map*) param;

    for (int i = 0; i < map->num_units; i++) {
        // 随机移动矩形
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;
        move_rect(&map->units[i].position, dx, dy);
    }

    // 返回下一次定时器的间隔
    return interval;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_TimerID timer = 0;

    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL初始化失败: %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    window = SDL_CreateWindow("SDL RTS游戏", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // 初始化地图
    Map map = { 0 };
    for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE; x++) {
        for (int y = 0; y < SCREEN_HEIGHT / TILE_SIZE; y++) {
            if (x == 0 || y == 0 || x == SCREEN_WIDTH / TILE_SIZE - 1 || y == SCREEN_HEIGHT / TILE_SIZE - 1) {
                map.tiles[x][y] = 1;
            }
        }
    }

    // 初始化单位
    map.units[0] = (Unit) { { 100, 100 }, 100 };
    map.units[1] = (Unit) { { 200, 200 }, 100 };
    map.num_units = 2;

    // 创建定时器
    timer = SDL_AddTimer(MOVE_INTERVAL, move_timer_callback, &map);

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

        // 绘制地图和单位
        draw_map(renderer, &map);

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
