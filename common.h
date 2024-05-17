#ifndef COMMON_H
#define COMMON_H

#include "SDL_utils.h"

using namespace std;

const int num_type = 5; // 20
const int max_number_fall = 200; // 100
const int easy = 5;
const int medium = 10;
const int hard = 13;
const int max_dem = 10;
const int insert_number_fall = 15;

//Fall.h
const int width_type = 61;
const int height_type = 61;

//monkey.h
const int width_monkey = 133;
const int height_monkey = 151;

SDL_Texture* loadTexture(SDL_Renderer* renderer, SDL_Texture* newTexture, const string& path);
Mix_Chunk* loadMusic(const string& path);
void RenderImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h);
bool CheckCollision(const SDL_Rect& fall_rand, const SDL_Rect& monkey);

#endif // COMMON_H
