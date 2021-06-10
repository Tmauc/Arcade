/*
** EPITECH PROJECT, 2019
** Gtk.hpp
** File description:
** gtk+ library for arcade
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

#include "ILib.hpp"

namespace Arcade
{

class Sfml : public ILib
{
private:
    sf::RenderWindow _app;
    sf::Texture _texture;
    sf::Font _font;

public:
    Sfml(void);
    ~Sfml(void);

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
        return new Sfml();
    }
}


}; // namespace Arcade
