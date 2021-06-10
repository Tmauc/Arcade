/*
** EPITECH PROJECT, 2019
** Game.hpp
** File description:
** Player
*/

#pragma once

#include "IGame.hpp"

namespace Arcade
{

class Nibbler : public IGame
{
private:
    bool _addOne = false;
    Pos _candyPos;
    Direction _next = Direction::UP;

    void movePlayer(Pos p_newPos);
    void createMap(void);
    void spawnCandy(void);
    bool verifyEnd(Direction p_dir);
    bool goTo(Direction p_dir);

public:
    Nibbler(size_t p_width = BASIC::WIDTH, size_t p_height = BASIC::HEIGHT);
    ~Nibbler(void) {};
    
    bool next_frame(KEYS p_ButtonPressed);
    void restart(void);
};

extern "C"
{
    IGame *newGame(void)
    {
        return new Nibbler();
    }
};

}; // namespace Arcade
