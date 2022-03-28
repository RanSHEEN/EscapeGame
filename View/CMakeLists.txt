cmake_minimum_required(VERSION 3.21)
project(View C)

set(CMAKE_C_STANDARD 99)
set(SDL_DIR "~/SDL")
include_directories(${SDL_DIR}/include/)
link_directories(${SDL_DIR}/lib/)
link_libraries(SDL2)

set(OpenGL_DIR "~/mesa-22.0.0")
include_directories(${OpenGL_DIR}/include/)
link_directories(${OpenGL_DIR}/lib/)
link_libraries(GL)

add_executable(View main.c window.c renderer.c texture.c texture.h event.c event.h)