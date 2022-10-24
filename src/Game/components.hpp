#ifndef JORGE_COMPONENTS_
#define JORGE_COMPONENTS_

#include <iostream>
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

struct BallSpeedComponent
{
    float v_x;
    float v_y;
};

#endif