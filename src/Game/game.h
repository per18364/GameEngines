#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    ~Game();

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
};
