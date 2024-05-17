#include <cstdlib>
#include <ctime>
#include "monkey.h"
#include "game.h"
#include "Fall.h"
#include "SDL_utils.h"

/*


        Made by: HieuSerend!


*/

using namespace std;

void RenderGameOver(SDL_Renderer* renderer, const int& score);
void RenderScore(SDL_Renderer* renderer, const int& score);
void RenderNumberFall(SDL_Renderer* renderer, const int& number_fall, const int& dem);
int PlayAgain(SDL_Renderer* renderer, SDL_Event e);
bool CheckPlayAgain(SDL_Event e);

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event e;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    bool CheckP;
    do
    {
        if (PlayAgain(renderer, e) == 0)
        {
            quitSDL(window, renderer);
            return 0;
        }
        CheckP = CheckPlayAgain(e);
    } while (CheckP);

    quitSDL(window, renderer);
    return 0;
}

int PlayAgain(SDL_Renderer* renderer, SDL_Event e)
{
    Game game(renderer);
    MonkeyX monkey(renderer);
    Music music;

    int x, y, speed;
    bool play = false;
    bool checkend = false;

    music.PlayStart();
    while (!checkend)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return 0;
            game.render_start(renderer);
            SDL_RenderPresent(renderer);
            if ( e.type == SDL_MOUSEBUTTONDOWN )
            {
                SDL_GetMouseState(&x, &y);
                if (e.button.button == SDL_BUTTON_LEFT && x>=930 && x<=990 && y>=10 && y<=70)
                {
                    checkend = true;
                    break;
                }
                if (e.button.button == SDL_BUTTON_LEFT && x>=650 && x<=980 && y>=480 && y<=630)
                {
                    checkend = true;
                    play = true;
                    break;
                }

            }
        }
        if (checkend){
            checkend = false;
            break;
        }
    }

    while (play == false && !checkend)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return 0;
            game.render_rules(renderer);
            SDL_RenderPresent(renderer);
            SDL_GetMouseState(&x, &y);
            if (e.type == SDL_MOUSEBUTTONDOWN)
                if (e.button.button == SDL_BUTTON_LEFT)
                    if (x>=650 && x<=980 && y>=480 && y<=630)
                    {
                        checkend = true;
                        play = true;
                    }
        }
        if (checkend){
            checkend = false;
            break;
        }
    }

    while (!checkend)
    {
        while (SDL_PollEvent(&e)!= 0)
        {
            if (e.type == SDL_QUIT) return 0;
            game.render_level(renderer);
            SDL_RenderPresent(renderer);
            SDL_GetMouseState(&x, &y);
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    if (x>=185 && x<=368 && y>=298 && y<=389)
                    {
                        speed = easy;
                        checkend = true;
                        break;
                    }
                    if (x>=415 && x<=598 && y>=298 && y<=389)
                    {
                        speed = medium;
                        checkend = true;
                        break;
                    }
                    if (x>=640 && x<= 823 && y>=298 && y<=389)
                    {
                        speed = hard;
                        checkend = true;
                        break;
                    }
                }
            }
        }
        if (checkend){
            checkend = false;
            break;
        }
    }

    Mix_HaltChannel(-1);

    FallRandom* falls = new FallRandom[num_type];
    int list_type[num_type];
    for (int i=0;i<num_type;i++)
    {
        FallRandom* fall_rand = (falls + i);
        if (fall_rand)
        {
            list_type[i] = fall_rand->chooseType(renderer, speed, i);
            fall_rand->resetType();
        } else cout << "Fail in initialize fall_rand \n";
    }

    music.PlayGame();

    //main loop
    int score = 0;
    int dem = 0;
    int number_fall = max_number_fall;
    while (play)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                delete [] falls;
                return 0;
            }
            game.render_bgg(renderer);
            monkey.HandleInputAction(e);
            monkey.render(renderer);

            for (int i=0;i<num_type;i++)
            {
                FallRandom* fall_rand = (falls + i);
                if (fall_rand)
                {
                    fall_rand->render(renderer);
                    fall_rand->HandleMove(speed);

                    bool check_col = CheckCollision(fall_rand->Type_Rect(), monkey.Monkey_Rect());
                    if (check_col)
                    {
                        music.PlayEat();
                        if (list_type[i] == BANANA)
                        {
                            dem++;
                            score += 3;
                            fall_rand->resetType();
                        }
                        if (list_type[i] == APPLE)
                        {
                            dem++;
                            score += 1;
                            fall_rand->resetType();
                        }
                        if (list_type[i] == SHIT)
                        {
                            dem = 0;
                            if (score >= 2) score -= 2;
                                else score = 0;
                            fall_rand->resetType();
                        }
                            if (list_type[i] == BOOM)
                        {
                            play = false;
                        }
                    } else
                        {
                            if (list_type[i] == BANANA || list_type[i] == APPLE)
                                if (fall_rand->getY() > SCREEN_HEIGHT - 5)
                                {
                                    number_fall--;
                                }
                            if (number_fall == 0) play = false;
                        }

                    if (dem == max_dem)
                    {
                        dem = 0;
                        number_fall += insert_number_fall;
                    }
                } else cout << "Fail in initialize fall_rand in main loop\n";
            }
            RenderNumberFall(renderer, number_fall, dem);
            RenderScore(renderer, score);

            SDL_RenderPresent(renderer);
            }

    }
    Mix_HaltChannel(-1);
    music.PlayGameOver();
    game.render_gameover(renderer);
    RenderGameOver(renderer, score);

    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    delete [] falls;
    return 1;
}

bool CheckPlayAgain(SDL_Event e)
{
    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) return false;
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (e.type == SDL_MOUSEBUTTONDOWN)
                if (e.button.button == SDL_BUTTON_LEFT)
                    if (x>=780 && x<=980 && y>=565 && y<=625)
                    {
                        return true;
                    }
        }
    }
}

void RenderGameOver(SDL_Renderer* renderer, const int& score)
{
    string score_s = to_string(score);
    Font overgame(50);
    overgame.SetColor(yellow);
    overgame.SetText(score_s);
    overgame.render(renderer, 540, 300, 120, 110);
}

void RenderScore(SDL_Renderer* renderer, const int& score)
{
    Font font_score(60);
    string score_s = to_string(score);
    font_score.SetText(score_s);
    font_score.render(renderer, 830, 57, 80, 90);
}

void RenderNumberFall(SDL_Renderer* renderer, const int& number_fall, const int& dem)
{
    Font font_skip(50);
    string s = to_string(number_fall);
    string ss = "Number of skips: " + s;
    font_skip.SetText(ss);
    font_skip.render(renderer, 10, 2, 250, 50);

    Font font_dem(50);
    string dem_s = to_string(dem);
    string dem_ss = "Fruits: " + dem_s + "/10";
    font_dem.SetText(dem_ss);
    font_dem.render(renderer, 10, 60, 180, 50);
}

