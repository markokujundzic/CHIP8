cmake_minimum_required(VERSION 3.17)
project(CHIP8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lmingw32 -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(CHIP8 src/main.cpp src/Chip8CPU.cpp src/Chip8CPU.h)

target_link_libraries(CHIP8 -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf)