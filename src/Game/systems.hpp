#include <iostream>
#include <string.h>
#include "game.h"
#include <SDL2/SDL.h>
#include "entt.hpp"
#include "components.hpp"

void Game::createPlayerSystem(int w, int h, std::string spriteName, SDL_Rect rect)
{
    r.emplace<PositionComponent>(p1, (world.w / 2) - (w / 2), (world.h / 2) - (h / 2));
    r.emplace<BoxComponent>(p1, w, h);
    SDL_Surface *surface = IMG_Load(spriteName.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    r.emplace<SpriteComponent>(p1, texture, rect);
    r.emplace<SpeedComponent>(p1, 0, 0);
    r.emplace<HitComponent>(p1, 3);

    camera.x = (world.w / 2) - (window_w / 2);
    camera.y = (world.h / 2) - (window_h / 2);
}

void Game::createEnemySystem(int w, int h, std::string spriteName, SDL_Rect rect)
{
    r.emplace<PositionComponent>(enemy, (world.w / 2) - (w / 2) + 500, (world.h / 2) - (h / 2) + 200);
    r.emplace<BoxComponent>(enemy, w, h);
    SDL_Surface *surface = IMG_Load(spriteName.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    r.emplace<SpriteComponent>(enemy, texture, rect);
    r.emplace<SpeedComponent>(enemy, 0, 0);
}

void Game::createBallSystem(entt::entity player, int x, int y, int w, int h, float v_x, float v_y)
{
    r.emplace<BoxComponent>(player, w, h);
    r.emplace<PositionComponent>(player, x, y);
    // r.emplace<BallSpeedComponent>(player, v_x, v_y);
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
    auto &speed = r.get<SpeedComponent>(p1);
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int move = 10;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            std::cout << "KEY PRESSED" << std::endl;

            if (state[SDL_SCANCODE_A])
            {
                speed.v_x = -move;
            }
            else if (state[SDL_SCANCODE_D])
            {
                speed.v_x = move;
            }

            if (state[SDL_SCANCODE_S])
            {
                speed.v_y = move;
            }
            else if (state[SDL_SCANCODE_W])
            {
                speed.v_y = -move;
            }
        }
        if (event.type == SDL_KEYUP)
        {
            std::cout << "KEY RELEASED" << std::endl;

            int key = event.key.keysym.sym;
            if (key == SDLK_a)
            {
                speed.v_x = 0;
            }
            else if (key == SDLK_d)
            {
                speed.v_x = 0;
            }

            if (key == SDLK_s)
            {
                speed.v_y = 0;
            }
            else if (key == SDLK_w)
            {
                speed.v_y = 0;
            }
        }
    }
    std::cout << "Player x: " << r.get<PositionComponent>(p1).x << std::endl;
    std::cout << "Player vx: " << r.get<SpeedComponent>(p1).v_x << std::endl;
}

void Game::limitSystem()
{
    if (r.get<PositionComponent>(p1).x <= 0)
    {
        r.get<PositionComponent>(p1).x = 0;
    }
    if (r.get<PositionComponent>(p1).y <= 0)
    {
        r.get<PositionComponent>(p1).y = 0;
    }

    if ((r.get<PositionComponent>(p1).x + r.get<BoxComponent>(p1).width) >= world.w)
    {
        r.get<PositionComponent>(p1).x = world.w - r.get<BoxComponent>(p1).width;
    }
    if ((r.get<PositionComponent>(p1).y + r.get<BoxComponent>(p1).height) >= world.h)
    {
        r.get<PositionComponent>(p1).y = world.h - r.get<BoxComponent>(p1).height;
    }

    if (r.get<PositionComponent>(p1).x > 11000 && r.get<PositionComponent>(p1).y > 11600)
    {
        std::cout << "YOU WON!! NOW GO SAVE YOUR DAD!!" << std::endl;
        isRunning = false;
    }
}

void Game::ballMovementSystem()
{

    // r.get<PositionComponent>(ball).y += r.get<BallSpeedComponent>(ball).v_y * delta_time;
    // if ((r.get<PositionComponent>(ball).y < 0) || (r.get<PositionComponent>(ball).y > (window_h - r.get<BoxComponent>(ball).height)))
    // {
    //     r.get<BallSpeedComponent>(ball).v_y *= -1.05f;
    // }

    // r.get<PositionComponent>(ball).x += r.get<BallSpeedComponent>(ball).v_x * delta_time;
    // if (r.get<BallSpeedComponent>(ball).v_x < 0)
    // {
    //     if ((r.get<PositionComponent>(ball).y + r.get<BoxComponent>(ball).height >= r.get<PositionComponent>(p1).y) && (r.get<PositionComponent>(ball).y <= r.get<PositionComponent>(p1).y + r.get<BoxComponent>(p1).height))
    //     {
    //         if (r.get<PositionComponent>(ball).x <= 0 + r.get<BoxComponent>(p1).width)
    //         {
    //             r.get<BallSpeedComponent>(ball).v_x *= -1.05f;
    //         }
    //     }
    //     if (r.get<PositionComponent>(ball).x <= 0)
    //     {
    //         std::cout << "Player 2 Won" << std::endl;
    //         isRunning = false;
    //     }
    // }

    // else if (r.get<BallSpeedComponent>(ball).v_x > 0)
    // {
    //     if ((r.get<PositionComponent>(ball).y + r.get<BoxComponent>(ball).height >= r.get<PositionComponent>(p2).y) && (r.get<PositionComponent>(ball).y <= r.get<PositionComponent>(p2).y + r.get<BoxComponent>(p2).height))
    //     {
    //         if (r.get<PositionComponent>(ball).x >= (window_w - r.get<BoxComponent>(ball).width - r.get<BoxComponent>(p2).width))
    //         {
    //             r.get<BallSpeedComponent>(ball).v_x *= -1.05f;
    //         }
    //     }
    //     if (r.get<PositionComponent>(ball).x >= window_w - r.get<BoxComponent>(ball).width)
    //     {
    //         std::cout << "Player 1 Won" << std::endl;
    //         isRunning = false;
    //     }
    // }
}

void Game::drawBackgroundSystems()
{
    SDL_Rect clip = {camera.x, camera.y, window_w, window_h};
    background->render(0, 0, window_w, window_h, &clip, 0, nullptr, SDL_FLIP_NONE);
}

void Game::movementSystem()
{
    const auto view = r.view<SpeedComponent, PositionComponent>();
    for (const auto e : view)
    {
        auto speed = view.get<SpeedComponent>(e);
        auto &position = view.get<PositionComponent>(e);

        position.x += speed.v_x;
        position.y += speed.v_y;
    }
}

void Game::drawPlayerSystem(SDL_Renderer *renderer)
{
    const auto view = r.view<SpriteComponent, BoxComponent, PositionComponent>();
    for (const auto e : view)
    {
        auto sprite = view.get<SpriteComponent>(e);
        auto box = view.get<BoxComponent>(e);
        auto position = view.get<PositionComponent>(e);
        SDL_Rect rect;
        rect.x = position.x - camera.x;
        rect.y = position.y - camera.y;
        rect.w = box.width;
        rect.h = box.height;

        SDL_RenderCopy(renderer, sprite.texture, nullptr, &rect);
    }
}

void Game::drawEnemySystem(SDL_Renderer *renderer)
{
    const auto view = r.view<SpriteComponent, BoxComponent, PositionComponent>();
    for (const auto e : view)
    {
        auto sprite = view.get<SpriteComponent>(e);
        auto box = view.get<BoxComponent>(e);
        auto position = view.get<PositionComponent>(e);
        SDL_Rect rect;
        rect.x = position.x;
        rect.y = position.y;
        rect.w = box.width;
        rect.h = box.height;

        SDL_RenderCopy(renderer, sprite.texture, nullptr, &rect);
    }
}

void Game::camerFollowSystem()
{
    const auto position = r.get<PositionComponent>(p1);
    const auto rect = r.get<BoxComponent>(p1);
    int cx = position.x - (window_w / 2) + (rect.width / 2);
    int cy = position.y - (window_h / 2) + (rect.height / 2);
    if (cx > 0 and cx < (world.w - window_w))
    {
        camera.x = cx;
    }
    if (cy > 0 and cy < (world.h - window_h))
    {
        camera.y = cy;
    }
}

void Game::enemyUpdateSystem()
{
    auto targetPos = r.get<PositionComponent>(p1);
    auto enemyPos = r.get<PositionComponent>(enemy);
    auto &speed = r.get<SpeedComponent>(enemy);
    int move = 3;

    // std::cout << "targetx: " << targetPos.x << std::endl;
    // std::cout << "enemyx: " << enemyPos.x << std::endl;

    if (enemyPos.x != targetPos.x)
    {
        if (enemyPos.x > targetPos.x)
        {
            speed.v_x = -move;
        }
        if (enemyPos.x < targetPos.x)
        {
            speed.v_x = move;
        }
    }
    else if (enemyPos.y != targetPos.y)
    {
        if (enemyPos.y > targetPos.y)
        {
            speed.v_y = -move;
        }
        if (enemyPos.y < targetPos.y)
        {
            speed.v_y = move;
        }
    }
}

void Game::collisionHandler()
{
    auto p = r.get<SpriteComponent>(p1).box;
    auto e = r.get<SpriteComponent>(enemy).box;
    auto tPos = r.get<PositionComponent>(p1);
    auto ePos = r.get<PositionComponent>(enemy);

    p.x = tPos.x;
    p.y = tPos.y;
    p.w = r.get<BoxComponent>(p1).width;
    p.h = r.get<BoxComponent>(p1).height;

    e.x = ePos.x;
    e.y = ePos.y;
    e.w = r.get<BoxComponent>(enemy).width;
    e.h = r.get<BoxComponent>(enemy).height;

    int speed = 10;
    int &hits = r.get<HitComponent>(p1).hp;

    if (SDL_HasIntersection(&p, &e))
    {
        if (ePos.y >= tPos.y)
        {
            r.get<PositionComponent>(p1).y -= 15 * speed;
            r.get<PositionComponent>(enemy).y += 4 * speed;
        }
        else if (ePos.y <= tPos.y)
        {
            r.get<PositionComponent>(p1).y += 15 * speed;
            r.get<PositionComponent>(enemy).y -= 4 * speed;
        }
        else if (ePos.x >= tPos.x)
        {
            r.get<PositionComponent>(p1).x -= 15 * speed;
            r.get<PositionComponent>(enemy).x += 4 * speed;
        }
        else if (ePos.x <= tPos.x)
        {
            r.get<PositionComponent>(p1).x += 15 * speed;
            r.get<PositionComponent>(enemy).x -= 4 * speed;
        }

        hits -= 1;
        std::cout << "hits: " << hits << std::endl;
    }

    if (hits == 0)
    {
        std::cout << "GAME OVER" << std::endl;
        isRunning = false;
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