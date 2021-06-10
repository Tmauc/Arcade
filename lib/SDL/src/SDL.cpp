/*
** EPITECH PROJECT, 2019
** SDL.cpp
** File description:
** gtk+ cpp file
*/

#include "SDL.hpp"

namespace Arcade
{

SDL::SDL(void) : ILib(), _screen(NULL), _renderer(NULL)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_CreateWindowAndRenderer(BASIC::WIDTH,
                                BASIC::HEIGHT,
                                SDL_WINDOW_SHOWN,
                                &(this->_screen),
                                &(this->_renderer));
    SDL_SetWindowTitle(this->_screen, "ARCADE SDL2");
    this->_textures = IMG_LoadTexture(this->_renderer, BLOCK_PATH);
};

SDL::~SDL(void)
{
    SDL_Quit();
    TTF_Quit();
};

KEYS SDL::get_key(void)
{
    SDL_Event event;
    
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            return KEYS::EXIT;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                return KEYS::LEFT;
            case SDLK_RIGHT:
                return KEYS::RIGHT;
            case SDLK_UP:
                return KEYS::UP;
            case SDLK_DOWN:
                return KEYS::DOWN;
            case SDLK_l:
                return KEYS::NEXT_LIB;
            case SDLK_k:
                return KEYS::PREV_LIB;
            case SDLK_p:
                return (KEYS::NEXT_GAME);
            case SDLK_o:
                return (KEYS::PREV_GAME);
            case SDLK_RETURN:
                return KEYS::RESTART;
            case SDLK_ESCAPE:
                return (KEYS::MENU);
            case SDLK_SPACE:
                return (KEYS::SPACE);
            case SDLK_1:
                return (KEYS::ONE);
            case SDLK_2:
                return (KEYS::TWO);
            case SDLK_3:
                return (KEYS::THREE);
            case SDLK_4:
                return (KEYS::FOUR);
            case SDLK_5:
                return (KEYS::FIVE);
            }
        }
    }
    return (KEYS::NO_KEY);
};

void SDL::draw_text(std::string p_str, Color p_color, Pos p_where, size_t p_size)
{
    TTF_Font *font = TTF_OpenFont("Ressource/fonts/Roboto-Light.ttf", p_size);
    SDL_Color color = {p_color.r, p_color.g, p_color.b, p_color.a};
    SDL_Surface *surface = TTF_RenderText_Solid(font, p_str.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
    int a = 0;
    int b = 0;

    SDL_QueryTexture(texture, NULL, NULL, &(a), &(b));
    SDL_Rect rect = {static_cast<int>(p_where.x), static_cast<int>(p_where.y), a, b};
    SDL_RenderCopy(this->_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
};

void SDL::draw_block(int p_x, int p_y, int p_id)
{
    SDL_Rect dstrect = {p_x, p_y, BLOCK_SIZE, BLOCK_SIZE};
    SDL_Rect srcrect = {BLOCK_SIZE * p_id, 0, BLOCK_SIZE, BLOCK_SIZE};

    SDL_RenderCopy(this->_renderer, this->_textures, &srcrect, &dstrect);
};

void SDL::close_window(void)
{
    SDL_DestroyTexture(this->_textures);
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_screen);
};

void SDL::update(void)
{
    SDL_RenderPresent(this->_renderer);
    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    clear();
};

void SDL::clear(void)
{
    SDL_RenderClear(this->_renderer);
}

}; // namespace Arcade
