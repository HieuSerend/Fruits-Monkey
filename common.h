#ifndef COMMON_H
#define COMMON_H

#include "utils.h"

using namespace std;

const int num_obj = 20;
const int max_number_fall = 100;
const int max_dem = 10;
const int insert_number_fall = 15;

const int WIDTH_OBJ = 61;
const int HEIGHT_OBJ = 61;

const int WIDTH_NEWTON = 133;
const int HEIGHT_NEWTON = 151;

SDL_Texture* loadTexture(SDL_Renderer* renderer, SDL_Texture* newTexture, const string& path);
Mix_Chunk* loadMusic(const string& path);
void RenderImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h);

#endif // COMMON_H
