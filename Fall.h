#ifndef FALL_H
#define FALL_H

#include "Common.h"

using namespace std;

enum
{
    BANANA,
    BOOM,
    APPLE,
    SHIT,
    TYPE
};


class FallRandom
{
private:
    SDL_Texture* type_image;
    int x, y, w, h;
    int y_;
    int type;

public:
    FallRandom();
    ~FallRandom();

    void HandleMove(const int& y_);
    void render(SDL_Renderer* renderer);
    void resetType();
    int chooseType(SDL_Renderer* renderer, const int& speed, const int& i);
    int getY() const { return y; }

    SDL_Rect Type_Rect();
};
#endif // FALL_H

