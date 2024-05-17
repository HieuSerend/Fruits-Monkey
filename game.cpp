#include "game.h"

//Game
Game::Game(SDL_Renderer* renderer)
{
    this -> background = loadTexture(renderer, background, "Picture/background.png");
    this -> start = loadTexture(renderer, start, "Picture/start.png");
    this -> rules = loadTexture(renderer, rules, "Picture/rules.png");
    this -> background2 = loadTexture(renderer, background2, "Picture/background2.1.bmp");
    this -> gameover = loadTexture(renderer, background2, "Picture/gameover1.bmp");
    this -> replay = loadTexture(renderer, replay, "Picture/replay.png");
    this -> level = loadTexture(renderer, level, "Picture/level.png");
}

Game::~Game()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(start);
    SDL_DestroyTexture(rules);
    SDL_DestroyTexture(background2);
    SDL_DestroyTexture(gameover);
    SDL_DestroyTexture(replay);
    SDL_DestroyTexture(level);
}

void Game::render_start(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, background, NULL, NULL);
    RenderImage(renderer, start, 650, 480, 330, 150); // 780 565 200 70
}

void Game::render_rules(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, rules, NULL, NULL);
    RenderImage(renderer, start, 650, 480, 330, 150);
}

void Game::render_bgg(SDL_Renderer* renderer)
{
    RenderImage(renderer, background2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::render_gameover(SDL_Renderer* renderer)
{
    RenderImage(renderer, gameover, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    RenderImage(renderer, replay, 780, 565, 200, 60);
}

void Game::render_level(SDL_Renderer* renderer)
{
    RenderImage(renderer, level, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

//Font
Font::Font(const int& size)
{
    color = {255, 255, 255}; //white color
    font = TTF_OpenFont("Sofia-Regular.otf", size);
}

Font::~Font()
{
    if (font)
    {
		TTF_CloseFont(font);
		font = NULL;
	}
    SDL_DestroyTexture(texture);
}

void Font::SetText(const string& text)
{
    text_ = text;
}

void Font::SetColor(const int& type)
{
    if (type == black) color = {0, 0, 0};
    if (type == yellow) color = {255, 255, 0};
}

SDL_Texture* Font::loadText(SDL_Renderer* renderer)
{
    SDL_Surface* surface = NULL;
	surface = TTF_RenderText_Solid(font, text_.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
        cout << "Unable to create texture from " << text_ << "\nSDL Error: " << SDL_GetError() << endl;
	SDL_FreeSurface(surface);
	return texture;
}

void Font::render(SDL_Renderer* renderer, int x, int y, int w, int h)
{
    texture = loadText(renderer);
    RenderImage(renderer, texture, x, y, w, h);
}

//Music
Music::Music()
{
    this->m_start = loadMusic("Music/backgr.ogg");
    this->m_bk = loadMusic("Music/play.ogg");
    this->m_eat = loadMusic("Music/eat.wav");
    this->m_go = loadMusic("Music/GameOver.wav");
}

Music::~Music()
{
    Mix_FreeChunk(m_start);
    Mix_FreeChunk(m_bk);
    Mix_FreeChunk(m_eat);
    Mix_FreeChunk(m_go);
}

void Music::PlayStart()
{
    Mix_PlayChannel(-1, m_start, -1);
}

void Music::PlayGame()
{
    Mix_PlayChannel(-1, m_bk, -1);
}

void Music::PlayEat()
{
    Mix_PlayChannel(-1, m_eat, 0);
}

void Music::PlayGameOver()
{
    Mix_PlayChannel(-1, m_go, 0);
}

