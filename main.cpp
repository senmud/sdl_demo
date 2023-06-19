#include <iostream>
#include <thread>
#include <SDL.h>
#include "event.h"
#include "texture.h"
#include "common.h"

#define SDL_CUSTOM_EVENT (SDL_USEREVENT+1)

#ifdef _TARGET_
int main(int argc, char* argv[])
{
    bool quit = false;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Init(SDL_INIT_VIDEO);                               //init sdl

    window = SDL_CreateWindow(                              //init window
            "First Window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window)
        return -1;
    renderer = SDL_CreateRenderer(window, -1, 0);           //init renderer
    if (!renderer)
        return -1;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);       //设置渲染器颜色
    SDL_RenderClear(renderer);                              //清理renderer
    SDL_RenderPresent(renderer);                            //绘制renderer

    SDL_Texture *target = loadTexture(std::string("/Users/ning/CLionProjects/sdl_demo/target_logo.png"), renderer);

    //启动线程，创建自定义的事件
    std::thread th([]() {
        SDL_Delay(3000);
        SDL_Event event;
        event.type = SDL_CUSTOM_EVENT;
        SDL_PushEvent(&event);
        //std::cout << "push custom event: " << event.type << std::endl;
        return 0;
    });

    SDL_Event windowsEvent;
    while (!quit)
    {
        while (SDL_PollEvent(&windowsEvent))
        {
            switch (windowsEvent.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    std::cout << "key down event" << std::endl;
                    break;
                case SDL_KEYUP:
                    std::cout << "key up event" << std::endl;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    //std::cout << "mouse button down event" << std::endl;
                    on_mouse_down(renderer, target);
                    break;
                case SDL_MOUSEMOTION:
                    on_mouse_move(renderer, target);
                    break;
                default:
                    std::cout << "event type=" << windowsEvent.type << " come" << std::endl;
                    break;
            }
        }
    }

    if (th.joinable())
        th.join();
    SDL_DestroyRenderer(renderer);                          //销毁renderer
    SDL_DestroyWindow(window);                              //销毁windows
    SDL_Quit();                                             //退出

    return 0;
}
#endif
