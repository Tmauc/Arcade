/*
** EPITECH PROJECT, 2019
** ILib.hpp
** File description:
** interface for graphical libs
*/

#pragma once

#include "Arcade.hpp"

namespace Arcade
{

class ILib
{
protected:
public:
    ILib(void) {};
    virtual ~ILib(void) = 0;

    virtual KEYS get_key(void) = 0;
    
    virtual void draw_text(std::string p_str, Color p_color, Pos p_where, size_t p_size) = 0;
    virtual void draw_block(int p_x, int p_y, int p_id) = 0;

    virtual void update(void) = 0;
    virtual void clear(void) = 0;
    virtual void close_window(void) = 0;
};

};
