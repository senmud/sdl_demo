//
// Created by Ning on 2023/4/27.
//
//以下是一个基于SDL库的简单的RTS游戏的示例代码，它使用C++编写。这个例子展示了如何使用SDL库创建一个窗口，加载图像，处理用户输入和渲染图像，并实现了一个简单的RTS游戏逻辑。

#include <SDL.h>
#include <vector>
#include <iostream>
#include "common.h"
#include "texture.h"

// 精灵类
class Sprite {
public:
    Sprite(SDL_Texture* texture, int x, int y) : m_texture(texture), m_x(x), m_y(y) {}

    void render(SDL_Renderer* renderer) {
        SDL_Rect rect = {m_x, m_y, 100, 100};
        SDL_RenderCopy(renderer, m_texture, nullptr, &rect);
    }

    bool contains(int x, int y) const {
        return x >= m_x && x < m_x + 100 && y >= m_y && y < m_y + 100;
    }

private:
    SDL_Texture* m_texture;
    int m_x, m_y;
};

#ifdef _RTS_GAME2_
int main(int argc, char* argv[]) {
    // 初始化SDL库
    SDL_Init(SDL_INIT_VIDEO);

    // 创建窗口
    SDL_Window* window = SDL_CreateWindow("RTS Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 加载图像
    SDL_Texture *texture = loadTexture("/Users/ning/Pictures/spirit2.jpeg", renderer);

    // 创建精灵
    std::vector<Sprite> sprites;
    sprites.emplace_back(texture, 100, 100);
    sprites.emplace_back(texture, 300, 300);

    // 游戏逻辑
    bool quit = false;
    SDL_Event event;
    int x = 0, y = 0;
    bool selecting = false;
    SDL_Rect selectRect = {0, 0, 0, 0};
    //int selectX = 0, selectY = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // 处理鼠标点击事件
                x = event.button.x;
                y = event.button.y;
                selecting = true;
                //selectX = x;
                //selectY = y;
                selectRect.x = x;
                selectRect.y = y;
                std::cout << "btn down: " << x << ", " << y << std::endl;
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                // 处理鼠标释放事件
                selecting = false;
                //x = event.button.x;
                //y = event.button.y;
                selectRect.h = event.button.y - selectRect.y;
                selectRect.w = event.button.x - selectRect.x;
                //int selectWidth = x - selectX;
                //int selectHeight = y - selectY;
                for (auto& sprite : sprites) {
                    if (sprite.contains(selectRect.x, selectRect.y) || sprite.contains(selectRect.x + selectRect.w, selectRect.y) ||
                        sprite.contains(selectRect.x, selectRect.y + selectRect.h) || sprite.contains(selectRect.x + selectRect.w, selectRect.y + selectRect.h)) {
                        // 选中精灵
                        sprite.render(renderer);
                    }
                }

                std::cout << "btn up: " << selecting << ", " << x << ", " << y << std::endl;
            }
        }

        // 渲染图像
        SDL_RenderClear(renderer);
        for (auto& sprite : sprites) {
            sprite.render(renderer);
        }

        // 渲染选择框
        if (selecting) {
            //SDL_Rect rect = {selectX, selectY, x - selectX, y - selectY};
            std::cout << "select: " << selectRect.x << ", " << selectRect.y << ", " << selectRect.h << ", " << selectRect.w << ", event: " << event.type << std::endl;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &selectRect);
        }

        SDL_RenderPresent(renderer);
    }

    // 清理资源
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
#endif

//这个例子创建了一个窗口，加载了一个名为“image.bmp”的图像，并在窗口中渲染了两个精灵。它还处理了用户退出事件和鼠标点击事件，并在窗口中渲染了一个选择框。当用户释放鼠标时，它会检查哪些精灵被选择，并在它们周围渲染一个框。您可以根据需要修改代码来实现自己的RTS游戏逻辑。