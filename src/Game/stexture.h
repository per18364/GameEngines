#ifndef JORGE_TEXTUREH_
#define JORGE_TEXTUREH_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class STexture
{

public:
    STexture(SDL_Renderer *gRenderer, SDL_Window *gWindow);
    ~STexture();
    void load(std::string path);

    void render(int x, int y, int w, int h, SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderWithShader(int x, int y, int w, int h, Uint32 (*func)(Uint32));

    int getWidth();
    int getHeight();

    // void free();

    int getPitch();
    int getPixelCount();

    Uint32 *getPixels();
    Uint32 getPixel(int x, int y);

    void executeShader(Uint32 (*func)(Uint32, STexture *), STexture *skin);

    void lockTexture();
    void unLockTexture();

private:
    SDL_Renderer *renderer;
    SDL_Window *window;

    int tWidth;
    int tHeight;

    Uint32 format;
    SDL_PixelFormat *mappingFormat;

    void *mPixels;
    int mPitch;

    SDL_Texture *mTexture;
};

#endif
