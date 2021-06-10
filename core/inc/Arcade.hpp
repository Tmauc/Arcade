/*
** EPITECH PROJECT, 2019
** Arcade.hpp
** File description:
** arcade main file
*/

#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>

#include "Errors.hpp"

namespace Arcade
{

#define BLOCK_SIZE 20
#define START_SIZE 4
#define BLOCK_PATH "Ressource/blocks.png"

const std::vector<std::string> trustedGames =
{
    "lib_arcade_nibbler.so",
    "lib_arcade_solarfox.so"
};

#define DEFAULT_GAME std::string("games/") + trustedGames[0]

const std::vector<std::string> trustedLibs =
{
    "lib_arcade_sdl2.so",
    "lib_arcade_sfml.so",
    "lib_arcade_ncurse.so"
};

struct Pos
{
    unsigned long int x;
    unsigned long int y;

    Pos &operator=(const Pos &p_other)
    {
        this->x = p_other.x;
        this->y = p_other.y;
        return (*this);
    };

    bool operator==(const Pos &p_pos)
    {
        return (this->x == p_pos.x && this->y == p_pos.y);
    };

    bool operator!=(const Pos &p_pos)
    {
        return !(*this == p_pos);
    };

};

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

enum BASIC
{
    WIDTH = 980,
    HEIGHT = 520
};

enum class Direction
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    UNDEFINED = 4
};

enum class KEYS
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    SPACE = 4,
    NEXT_LIB,
    PREV_LIB,
    NEXT_GAME,
    PREV_GAME,
    EXIT,
    MENU,
    RESTART,
    NO_KEY,
    NO_BUT,
    NO_BUT2,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
};

}; // namespace Arcade
