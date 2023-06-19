#include <cstdlib>
#include <SDL.h>
#include <cmath>
#include "common.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct {
    int x;
    int y;
} Vector2;

typedef struct {
    Vector2 position;
    int health;
    int damage;
} Unit;

typedef struct {
    Vector2 position;
    int health;
} Enemy;

typedef struct {
    Unit unit;
    bool selected;
} Player;

Player player;
Enemy enemy;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("RTS Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    player.unit.position.x = SCREEN_WIDTH / 2;
    player.unit.position.y = SCREEN_HEIGHT / 2;
    player.unit.health = 100;
    player.unit.damage = 10;
    player.selected = false;
    enemy.position.x = SCREEN_WIDTH / 4;
    enemy.position.y = SCREEN_HEIGHT / 4;
    enemy.health = 50;
}

void handle_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    player.selected = true;
                    player.unit.position.x = event.button.x;
                    player.unit.position.y = event.button.y;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    player.selected = false;
                }
                break;
            default:
                break;
        }
    }
}

void update() {
    if (player.selected) {
        Vector2 direction = {0, 0};
        SDL_GetMouseState(&direction.x, &direction.y);
        direction.x -= player.unit.position.x;
        direction.y -= player.unit.position.y;
        auto length = (float)std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction.x /= (int)length;
            direction.y /= (int)length;
        }
        player.unit.position.x += direction.x * 5;
        player.unit.position.y += direction.y * 5;
    }
    if (SDL_HasIntersection(&(SDL_Rect){player.unit.position.x, player.unit.position.y, 32, 32}, &(SDL_Rect){enemy.position.x, enemy.position.y, 32, 32})) {
        enemy.health -= player.unit.damage;
        if (enemy.health <= 0) {
            enemy.position.x = std::rand() % SCREEN_WIDTH;
            enemy.position.y = std::rand() % SCREEN_HEIGHT;
            enemy.health = 50;
        }
    }
}

void render() {
    SDL_Rect player_rect = {player.unit.position.x, player.unit.position.y, 32, 32};
    SDL_Rect enemy_rect = {enemy.position.x, enemy.position.y, 32, 32};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player_rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &enemy_rect);
    SDL_RenderPresent(renderer);
}

#ifdef _RTS_GAME
int main() {
    init();
    while (true) {
        handle_input();
        update();
        render();
        SDL_Delay(16);
    }
    return 0;
}
#endif
