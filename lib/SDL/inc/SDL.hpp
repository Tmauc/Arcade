/*
** EPITECH PROJECT, 2019
** Gtk.hpp
** File description:
** gtk+ library for arcade
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "ILib.hpp"

namespace Arcade
{

class SDL : public ILib
{
private:
    SDL_Window *_screen;
    SDL_Renderer *_renderer;
    SDL_Texture *_textures;
    std::vector<SDL_Rect> _rect;

public:
    SDL(void);
    ~SDL(void);

    KEYS get_key(void);

    void draw_text(std::string p_str, Color p_color, Pos p_where, size_t p_size);
    void draw_block(int p_x, int p_y, int p_id);

    void update(void);
    void clear(void);
    void close_window(void);
};

extern "C"
{
    ILib *newLib(void)
    {
        return new SDL();
    }
}


}; // namespace Arcade
