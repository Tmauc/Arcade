/*
** EPITECH PROJECT, 2019
** IGame.hpp
** File description:
** interface for game class
*/

#pragma once

#include <tuple>

#include "Arcade.hpp"

namespace Arcade
{

class IGame
{
protected:
    Direction _current = Direction::UNDEFINED;
    Pos _mapSize;
    size_t _score = 0;

    std::vector<Pos> _pos;
    std::vector<std::pair<Pos, Direction>> _ennemies;
    std::vector<std::vector<size_t>> _map;
    std::vector<std::tuple<Pos, Direction, int>> _shots;
    std::vector<std::pair<Pos, Direction>> _ennemiesShots;

    virtual void createMap(void) = 0;
    virtual bool goTo(Direction p_dir) = 0;

public:
    IGame(size_t p_width = BASIC::WIDTH, size_t p_height = BASIC::HEIGHT) {
        this->_mapSize.x = p_width / BLOCK_SIZE;
        this->_mapSize.y = p_height / BLOCK_SIZE;
    };
    virtual ~IGame(void) = 0;

    virtual bool next_frame(KEYS p_buttonPressed) = 0;
    virtual void restart(void) = 0;
    size_t getScore(void) { return (this->_score); };

    const Pos size(void) { return this->_mapSize; };
    std::vector<Pos> getPlayerPos(void) { return this->_pos; };
    std::vector<std::tuple<Pos, Direction, int>> getShotPos(void) { return this->_shots; };
    std::vector<std::pair<Pos, Direction>> getEnnemiesPos(void) { return this->_ennemies; };
    std::vector<std::pair<Pos, Direction>> getEnnemiesShot(void) { return this->_ennemiesShots; };
    
    const std::vector<size_t> &operator[](const size_t p_index) const {
        return (this->_map[p_index]);
    };

    const size_t &operator[](const Pos p_index) const {
        return (this->_map[p_index.y][p_index.x]);
    };

};

}; // namespace Arcade
