cmake_minimum_required(VERSION 3.22)

project(PONG VERSION 1.0)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src/Game)
# add_subdirectory(deps/SDL)
add_subdirectory(deps/Lua)


target_include_directories(
    ${PROJECT_NAME} PUBLIC src/Game
    # ${PROJECT_NAME} PUBLIC deps/SDL/src
    ${PROJECT_NAME} PUBLIC deps/Lua/lua-5.4.4/include
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE src/Game
    # ${PROJECT_NAME} PRIVATE deps/SDL/src
    ${PROJECT_NAME} PRIVATE deps/Lua/lua-5.4.4
)

target_link_libraries(
    ${PROJECT_NAME}
    game
    stexture
    SDL2
    SDL2main
    SDL2_image
    lua_static
)