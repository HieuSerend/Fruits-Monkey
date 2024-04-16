#include <cstdlib>
#include <ctime>
#include "utils.h"

using namespace std;

/*


    Idea and content by me, Hieeuserend


*/

int main (int argc, char* agrv[]){

    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    SDL_Event e;

    initSDL(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    while (true){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT) return 0;
        }
    }

    return 0;

}
