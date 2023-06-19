cmake_minimum_required(VERSION 3.23)
project(sdl_demo)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/local/sdl2/include/SDL2")
include_directories("/usr/local/sdl2_image/include/SDL2")
link_directories("/usr/local/sdl2/lib/")
link_directories("/usr/local/sdl2_image/lib")
link_libraries(SDL2)
link_libraries(SDL2_image)
add_compile_options(-Wno-address-of-temporary)

add_executable(sdl_demo main.cpp event.h event.cpp texture.h texture.cpp rts.cpp common.h demo1.cpp rts2.cpp rts3.cpp rts4.cpp move.cpp move2.cpp)

target_link_libraries(sdl_demo SDL2)
target_link_libraries(sdl_demo SDL2_image)