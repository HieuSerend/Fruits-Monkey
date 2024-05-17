#include "Common.h"

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
        cout << "Error Music: %s \n" << Mix_GetError();
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

//hàm CheckCollision tham khảo ở phattrienphanmem123az.com
bool CheckCollision(const SDL_Rect& fall_rand, const SDL_Rect& monkey)
{
    int left_a = fall_rand.x;
    int right_a = fall_rand.x + fall_rand.w;
    int top_a = fall_rand.y;
    int bottom_a = fall_rand.y + fall_rand.h;

    int left_b = monkey.x;
    int right_b = monkey.x + monkey.w;
    int top_b = monkey.y;
    int bottom_b = monkey.y + monkey.h;

    //chỉ đúng khi size fall_rand < monkey
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }
    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }
    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }
    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }
    return false;
}

