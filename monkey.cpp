#include "monkey.h"

MonkeyX::MonkeyX (SDL_Renderer* renderer)
{
    this -> monkey_ = loadTexture(renderer, monkey_, "Picture/monkey1.bmp");
    this -> x = (SCREEN_WIDTH - width_monkey)/2;
    this -> y = SCREEN_HEIGHT - height_monkey - 3 ;
    this -> w = width_monkey;
    this -> h = height_monkey;
}

MonkeyX::~MonkeyX()
{
    SDL_DestroyTexture(monkey_);
}

void MonkeyX::HandleInputAction(SDL_Event &e)
{
    int x_mouse, y_mouse;
    SDL_GetMouseState(&x_mouse, &y_mouse);
    if (x_mouse < width_monkey/2) x = 0;
        else if (x_mouse > (SCREEN_WIDTH - width_monkey/2)) x = SCREEN_WIDTH - width_monkey;
            else x = x_mouse - width_monkey/2;
}

void MonkeyX::render(SDL_Renderer* renderer)
{
    RenderImage(renderer, monkey_, x, y, w, h);
}

