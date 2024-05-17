#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL_mixer.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;
const string WINDOW_TITLE = "Newton game - Hieuserend";

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             int SCREEN_WIDTH, int SCREEN_HEIGHT, const string &WINDOW_TITLE);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

#endif

