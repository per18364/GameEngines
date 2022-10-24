#include <iostream>
#include "game.h"
#include <SDL2/SDL.h>
#include "entt.hpp"
#include "components.hpp"

void Game::createPlayerSystem(entt::entity player, int x, int y, int w, int h)
{
    r.emplace<PositionComponent>(player, x, y);
    r.emplace<BoxComponent>(player, w, h);
}

void Game::createBallSystem(entt::entity player, int x, int y, int w, int h, float v_x, float v_y)
{
    r.emplace<BoxComponent>(player, w, h);
    r.emplace<PositionComponent>(player, x, y);
    r.emplace<BallSpeedComponent>(player, v_x, v_y);
}

void Game::boxRenderSystem(SDL_Renderer *renderer)
{
    const auto view = r.view<BoxComponent, PositionComponent>();
    for (const auto e : view)
    {
        auto box = view.get<BoxComponent>(e);
        auto position = view.get<PositionComponent>(e);
        SDL_Rect rect;
        rect.x = position.x;
        rect.y = position.y;
        rect.w = box.width;
        rect.h = box.height;
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Game::handleEventSystem()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            std::cout << "KEY PRESSED" << std::endl;

            if (event.key.keysym.sym == SDLK_UP)
            {
                r.get<PositionComponent>(p2).y -= 10;
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                r.get<PositionComponent>(p2).y += 10;
            }

            if (event.key.keysym.sym == SDLK_s)
            {
                r.get<PositionComponent>(p1).y += 10;
            }
            else if (event.key.keysym.sym == SDLK_w)
            {
                r.get<PositionComponent>(p1).y -= 10;
            }
        }
    }
}

void Game::limitSystem()
{
    if (r.get<PositionComponent>(p2).y >= window_h - r.get<BoxComponent>(p2).height)
    {
        r.get<PositionComponent>(p2).y = window_h - r.get<BoxComponent>(p2).height;
    }

    if (r.get<PositionComponent>(p2).y <= 0)
    {
        r.get<PositionComponent>(p2).y = 0;
    }

    if (r.get<PositionComponent>(p1).y >= window_h - r.get<BoxComponent>(p1).height)
    {
        r.get<PositionComponent>(p1).y = window_h - r.get<BoxComponent>(p1).height;
    }

    if (r.get<PositionComponent>(p1).y <= 0)
    {
        r.get<PositionComponent>(p1).y = 0;
    }
}

void Game::ballMovementSystem()
{

    r.get<PositionComponent>(ball).y += r.get<BallSpeedComponent>(ball).v_y * delta_time;
    if ((r.get<PositionComponent>(ball).y < 0) || (r.get<PositionComponent>(ball).y > (window_h - r.get<BoxComponent>(ball).height)))
    {
        r.get<BallSpeedComponent>(ball).v_y *= -1.05f;
    }

    r.get<PositionComponent>(ball).x += r.get<BallSpeedComponent>(ball).v_x * delta_time;
    if (r.get<BallSpeedComponent>(ball).v_x < 0)
    {
        if ((r.get<PositionComponent>(ball).y + r.get<BoxComponent>(ball).height >= r.get<PositionComponent>(p1).y) && (r.get<PositionComponent>(ball).y <= r.get<PositionComponent>(p1).y + r.get<BoxComponent>(p1).height))
        {
            if (r.get<PositionComponent>(ball).x <= 0 + r.get<BoxComponent>(p1).width)
            {
                r.get<BallSpeedComponent>(ball).v_x *= -1.05f;
            }
        }
        if (r.get<PositionComponent>(ball).x <= 0)
        {
            std::cout << "Player 2 Won" << std::endl;
            isRunning = false;
        }
    }

    else if (r.get<BallSpeedComponent>(ball).v_x > 0)
    {
        if ((r.get<PositionComponent>(ball).y + r.get<BoxComponent>(ball).height >= r.get<PositionComponent>(p2).y) && (r.get<PositionComponent>(ball).y <= r.get<PositionComponent>(p2).y + r.get<BoxComponent>(p2).height))
        {
            if (r.get<PositionComponent>(ball).x >= (window_w - r.get<BoxComponent>(ball).width - r.get<BoxComponent>(p2).width))
            {
                r.get<BallSpeedComponent>(ball).v_x *= -1.05f;
            }
        }
        if (r.get<PositionComponent>(ball).x >= window_w - r.get<BoxComponent>(ball).width)
        {
            std::cout << "Player 1 Won" << std::endl;
            isRunning = false;
        }
    }
}

// void Game::fallSystem()
// {
//     const auto view = r.view<Position>();
//     for (const auto e : view)
//     {
//         auto *position = view.get<Position>(e);

//         position.y += 1;
//     }
// }