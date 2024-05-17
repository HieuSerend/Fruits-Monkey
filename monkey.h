#ifndef MONKEY_H
#define MONKEY_H

#include "Common.h"

class MonkeyX
{
private:
    SDL_Texture* monkey_;
    int x, y, w, h;
public:
    MonkeyX(SDL_Renderer* renderer);
    ~MonkeyX();

    void HandleInputAction(SDL_Event &e);
    void render(SDL_Renderer* renderer);

    SDL_Rect Monkey_Rect()
    {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        return rect;
    }
};

#endif // MONKEY_H
