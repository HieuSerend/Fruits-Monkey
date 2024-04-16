#include "common.h"

using namespace std;

SDL_Texture* loadTexture(SDL_Renderer* renderer, SDL_Texture* newTexture, const string& path)
{
    SDL_Surface* loadedSurface =  IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface -> format, 0, 255, 255));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL)
        {
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

Mix_Chunk* loadMusic(const string& path)
{
    Mix_Chunk* new_music = Mix_LoadWAV(path.c_str());
    if (new_music == NULL)
    {
        cout << "Error Music: %s \n" << Mix_GetError();
    }
    return new_music;
}

void RenderImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h)
{
    SDL_Rect Rect;
    Rect.x = x;
    Rect.y = y;
    Rect.w = w;
    Rect.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &Rect);
}

