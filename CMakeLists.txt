cmake_minimum_required(VERSION 3.10)
project(RaylibApplicationBuilder)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(appbuilder main.c src/lexer.c)

# Find the Raylib library
find_library(RAYLIB_LIBRARY raylib PATHS /opt/homebrew/Cellar/raylib/4.5.0/lib)
if(NOT RAYLIB_LIBRARY)
    message(FATAL_ERROR "raylib library not found")
endif()

# Include Raylib headers
include_directories(/opt/homebrew/Cellar/raylib/4.5.0/include)

# Link the Raylib library
target_link_libraries(appbuilder ${RAYLIB_LIBRARY})
