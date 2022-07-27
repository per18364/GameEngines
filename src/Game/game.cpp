#include <iostream>
#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int width, int height)
{
    std::cout << "Game Starting Up..." << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(title, 0, 0, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    isRunning = true;
}

void Game::setup()
{
    std::cout << "Game Setting Up..." << std::endl;

    SDL_GetRendererOutputSize(renderer, &window_w, &window_h);

    player1.x = 5;
    player1.y = 200;
    player1.w = 20;
    player1.h = window_h / 4;

    player2.y = 200;
    player2.w = 20;
    player2.x = (window_w - 5) - player2.w;
    player2.h = window_h / 4;

    ball.x = 350;
    ball.y = 350;
    ball.w = 25;
    ball.h = 25;
}

void Game::handleEvents()
{
    std::cout << "Game Handling Event..." << std::endl;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            std::cout << "KEY PRESSED" << std::endl;

            if (event.key.keysym.sym == SDLK_UP)
            {
                player2.y -= 10;
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                player2.y += 10;
            }

            if (event.key.keysym.sym == SDLK_s)
            {
                player1.y += 10;
            }
            else if (event.key.keysym.sym == SDLK_w)
            {
                player1.y -= 10;
            }
        }
    }
}

void Game::update()
{
    std::cout << "Game Updating..." << std::endl;

    if (player2.y >= window_w - player2.h)
    {
        player2.y = window_w - player2.h;
    }

    if (player2.y <= 0)
    {
        player2.y = 0;
    }

    if (player1.y >= window_w - player1.h)
    {
        player1.y = window_w - player1.h;
    }

    if (player1.y <= 0)
    {
        player1.y = 0;
    }

    ball.y += ball_y_speed * delta_time;
    if ((ball.y < 0) || (ball.y > (window_h - ball.h)))
    {
        ball_y_speed *= -1.05f;
    }

    ball.x += ball_x_speed * delta_time;
    if (ball_x_speed < 0)
    {
        if ((ball.y + ball.h >= player1.y) && (ball.y <= player1.y + player1.h))
        {
            if (ball.x <= 0 + player1.w)
            {
                ball_x_speed *= -1.05f;
            }
        }
        if (ball.x <= 0)
        {
            std::cout << "Player 2 Won" << std::endl;
            isRunning = false;
        }
    }

    else if (ball_x_speed > 0)
    {
        if ((ball.y + ball.h >= player2.y) && (ball.y <= player2.y + player2.h))
        {
            if (ball.x >= (window_w - ball.w - player2.w))
            {
                ball_x_speed *= -1.05f;
            }
        }
        if (ball.x >= window_w - ball.w)
        {
            std::cout << "Player 1 Won" << std::endl;
            isRunning = false;
        }
    }
}

void Game::render()
{
    std::cout << "Game Rendering..." << std::endl;
    SDL_SetRenderDrawColor(renderer, 34, 139, 34, 1);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    SDL_RenderFillRect(renderer, &player1);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    SDL_RenderFillRect(renderer, &player2);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    SDL_RenderFillRect(renderer, &ball);

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    std::cout << "Game Cleaning Up..." << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Over..." << std::endl;
}

bool Game::running()
{
    return isRunning;
}