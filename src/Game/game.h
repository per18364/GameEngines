#ifndef JORGE_GAME_
#define JORGE_GAME_

#include <SDL2/SDL.h>
#include "entt.hpp"
#include "stexture.h"

struct Camera
{
    int x;
    int y;
};

struct World
{
    int w;
    int h;
};

class Game
{
public:
    Game();
    ~Game();

    int startClock;
    int fps;

    __int64_t prev_time;
    __int64_t curr_time;
    __int64_t delta_time;

    void init(const char *title, int width, int height);

    void setup();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

    entt::registry r;

    void boxRenderSystem(SDL_Renderer *renderer);
    void createPlayerSystem(int w, int h, std::string spriteName, SDL_Rect rect);
    void createEnemySystem(int w, int h, std::string spriteName, SDL_Rect rect);
    void createBallSystem(entt::entity player, int x, int y, int w, int h, float v_x, float v_y);
    void handleEventSystem();
    void limitSystem();
    void ballMovementSystem();
    void movementSystem();
    void camerFollowSystem();
    void enemyUpdateSystem();
    void collisionHandler();

    void drawBackgroundSystems();
    void drawPlayerSystem(SDL_Renderer *renderer);
    void drawEnemySystem(SDL_Renderer *renderer);

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Rect p1Rect;
    SDL_Rect enemyRect;
    // SDL_Rect ball;

    int window_w, window_h;

    float ball_x_speed = 0.2f;
    float ball_y_speed = 0.2f;

    entt::entity p1;
    entt::entity enemy;
    Camera camera;
    World world;
    // entt::entity p2;
    // entt::entity ball;

    STexture *background;
};

#endif