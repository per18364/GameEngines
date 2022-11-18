#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "stexture.h"

STexture::STexture(SDL_Renderer *gRenderer, SDL_Window *gWindow)
{
    renderer = gRenderer;
    window = gWindow;

    tHeight = 0;
    tWidth = 0;
    mPitch = 0;

    format = SDL_GetWindowPixelFormat(window);
    mappingFormat = SDL_AllocFormat(format);
}

STexture::~STexture()
{
    SDL_FreeFormat(mappingFormat);
    SDL_DestroyTexture(mTexture);
    mPixels = nullptr;
}

void STexture::load(std::string path)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    SDL_Surface *formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, format, 0);

    mTexture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, loadedSurface->w, loadedSurface->h);

    tWidth = formattedSurface->w;
    tHeight = formattedSurface->h;

    lockTexture();

    memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

    unLockTexture();

    SDL_FreeSurface(loadedSurface);
    SDL_FreeSurface(formattedSurface);
}

int STexture::getPitch()
{
    return mPitch;
}

int STexture::getWidth()
{
    return tWidth;
}

int STexture::getHeight()
{
    return tHeight;
}

void STexture::render(int x, int y, int w, int h, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, w, h};

    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void STexture::renderWithShader(int x, int y, int w, int h, Uint32 (*func)(Uint32))
{
    SDL_Rect renderQuad = {x, y, w, h};

    lockTexture();

    Uint32 *pixels = getPixels();
    SDL_Texture *copyTexture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, tWidth, tHeight);
    void *copyPixels;
    int copyPitch;
    SDL_LockTexture(copyTexture, NULL, &copyPixels, &copyPitch);
    Uint32 *copyPixelsInt = (Uint32 *)copyPixels;

    for (int i = 0; i < getPixelCount(); i++)
    {
        copyPixelsInt[i] = func(pixels[i]);
    }

    SDL_RenderCopy(renderer, copyTexture, nullptr, &renderQuad);

    SDL_UnlockTexture(copyTexture);
    SDL_DestroyTexture(copyTexture);
    unLockTexture();
}

void STexture::lockTexture()
{
    SDL_LockTexture(mTexture, nullptr, &mPixels, &mPitch);
}
void STexture::unLockTexture()
{
    SDL_UnlockTexture(mTexture);
    mPixels = nullptr;
    mPitch = 0;
}

int STexture::getPixelCount()
{
    return tWidth * tHeight;
}

Uint32 *STexture::getPixels()
{
    return (Uint32 *)mPixels;
}

Uint32 STexture::getPixel(int x, int y)
{
    lockTexture();
    Uint32 *pixels = getPixels();
    Uint32 pixel = pixels[y * tWidth + x];
    unLockTexture();
    return pixel;
}

void STexture::executeShader(Uint32 (*func)(Uint32, STexture *), STexture *skin)
{
    lockTexture();
    Uint32 *pixels = getPixels();

    for (int i = 0; i < getPixelCount(); i++)
    {
        pixels[i] = func(pixels[i], skin);
    }

    unLockTexture();
}

// void free()
// {
//     SDL_DestroyTexture(mTexture);
// }