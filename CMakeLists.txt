cmake_minimum_required(VERSION 3.22)

project(PONG VERSION 1.0)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src/Game)
add_subdirectory(deps/SDL)

target_include_directories(
    ${PROJECT_NAME} PUBLIC src/Game
    ${PROJECT_NAME} PUBLIC deps/SDL/src
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE src/Game
    ${PROJECT_NAME} PRIVATE deps/SDL/src
)

target_link_libraries(
    ${PROJECT_NAME}
    game
    SDL2
    SDL2main
    SDL2_image
)