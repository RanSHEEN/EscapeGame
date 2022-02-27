cmake_minimum_required(VERSION 3.21)
project(View C)

set(CMAKE_C_STANDARD 99)
set(SDL_DIR "~/SDL")
include_directories(${SDL_DIR}/include/)
link_directories(${SDL_DIR}/lib/)
link_libraries(SDL2)

add_executable(View main.c)