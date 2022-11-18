#ifndef JORGE_COMPONENTS_
#define JORGE_COMPONENTS_

#include <iostream>
#include <SDL2/SDL.h>
#include <string.h>

struct Name
{
    std::string name;
};

struct BoxComponent
{
    int width;
    int height;
};

struct PositionComponent
{
    int x;
    int y;
};

struct SpeedComponent
{
    int v_x;
    int v_y;
};
struct SpriteComponent
{
    // std::string name;
    SDL_Texture *texture;
    SDL_Rect box;
};

struct HitComponent
{
    int hp;
};

#endif