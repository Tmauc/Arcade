/*
** EPITECH PROJECT, 2019
** Solar_fox.hpp
** File description:
** Solar_fox
*/

#pragma once

#include "IGame.hpp"

namespace Arcade
{

#define SPEED 1
#define SHOT_SPEED 4
#define ENNEMY_SHOT_SPEED 2
#define ENNEMY_SPEED 2
#define SHOT_DURATION 10
#define SHOT_CD 20
#define BORDER_SIZE 3

class SolarFox : public IGame
{
private:
    double _speed = SPEED;
    double _shotSpeed = SHOT_SPEED;
    Direction _next = Direction::UNDEFINED;

    void createMap(void);
    bool goTo(Direction p_dir);
    void updateShot(KEYS p_ButtonPressed);
    void updateEnnemies(void);
    void ennemiesShot(void);

public:
    SolarFox(size_t p_width = BASIC::WIDTH, size_t p_height = BASIC::HEIGHT);
    ~SolarFox(void);
    
    bool next_frame(KEYS p_ButtonPressed);
    void restart(void);
};

extern "C"
{
    IGame *newGame(void)
    {
        return new SolarFox();
    }
};

}; // namespace Arcade
