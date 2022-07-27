#include <SDL2/SDL.h>

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

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Rect player1;
    SDL_Rect player2;
    SDL_Rect ball;

    int window_w, window_h;

    float ball_x_speed = 0.2f;
    float ball_y_speed = 0.2f;
};
