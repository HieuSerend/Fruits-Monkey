#ifndef GAME_H
#define GAME_H

#include "Common.h"

class Game
{
private:
    SDL_Texture* background;
    SDL_Texture* start;
    SDL_Texture* rules;
    SDL_Texture* background2;
    SDL_Texture* gameover;
    SDL_Texture* replay;
    SDL_Texture* level;
public:
    Game(SDL_Renderer* renderer);
    ~Game();

    void render_start(SDL_Renderer* renderer);
    void render_rules(SDL_Renderer* renderer);
    void render_bgg(SDL_Renderer* renderer);
    void render_gameover(SDL_Renderer* renderer);
    void render_level(SDL_Renderer* renderer);
};

enum Color
{
    black,
    yellow
};

class Font
{
private:
    string text_;
    SDL_Color color;
    TTF_Font* font = NULL;
	SDL_Texture* texture;
public:
    Font(const int& size);
    ~Font();

    void SetText(const string& text);
    void SetColor(const int& type);
    void render(SDL_Renderer* renderer, int x, int y, int w, int h);
    SDL_Texture* loadText(SDL_Renderer* renderer);
};

class Music
{
private:
    Mix_Chunk* m_start;
    Mix_Chunk* m_bk;
    Mix_Chunk* m_eat;
    Mix_Chunk* m_go;
public:
    Music();
    ~Music();

    void PlayStart();
    void PlayGame();
    void PlayEat();
    void PlayGameOver();
};

#endif
