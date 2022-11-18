#include <iostream>
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "stexture.h"
#include "entt.hpp"
#include "components.hpp"
#include "systems.hpp"

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

    background = new STexture(renderer, window);
    background->load("./src/tilemap.png");

    world = World{12800, 12800};

    p1 = r.create();
    enemy = r.create();
    // p2 = r.create();
    // ball = r.create();

    // r.emplace<Name>(p1, "p1");
    createPlayerSystem(100, 100, "./src/Rei2.0.png", p1Rect);
    createEnemySystem(50, 50, "./src/Enemy.png", enemyRect);

    // r.emplace<Name>(p2, "p2");
    // createPlayerSystem(p2, (window_w - 5) - 20, 200, 20, window_h / 4);

    // r.emplace<Name>(ball, "ball");
    // createBallSystem(ball, 350, 350, 20, 20, 0.2f, 0.2f);

    // player1.x = 5;
    // player1.y = 200;
    // player1.w = 20;
    // player1.h = window_h / 4;

    // player2.y = 200;
    // player2.w = 20;
    // player2.x = (window_w - 5) - player2.w;
    // player2.h = window_h / 4;

    // ball.x = 350;
    // ball.y = 350;
    // ball.w = 200;
    // ball.h = 200;
}

void Game::handleEvents()
{
    std::cout << "Game Handling Event..." << std::endl;

    handleEventSystem();
}

void Game::update()
{
    std::cout << "Game Updating..." << std::endl;

    limitSystem();
    camerFollowSystem();
    enemyUpdateSystem();
    collisionHandler();
    movementSystem();
}

void Game::render()
{
    std::cout << "Game Rendering..." << std::endl;
    SDL_SetRenderDrawColor(renderer, 34, 139, 34, 1);
    SDL_RenderClear(renderer);

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);

    // boxRenderSystem(renderer);

    drawBackgroundSystems();
    drawPlayerSystem(renderer);
    drawEnemySystem(renderer);

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