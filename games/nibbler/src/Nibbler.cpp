/*
** EPITECH PROJECT, 2019
** Game.cpp
** File description:
** player
*/

#include "Nibbler.hpp"

namespace Arcade
{

Nibbler::Nibbler(size_t p_width, size_t p_height) : IGame(p_width, p_height)
{
    size_t player_startX =
        (std::rand() % (this->_mapSize.x - (START_SIZE * 2))) + START_SIZE;
    size_t player_startY =
        (std::rand() % (this->_mapSize.y - (START_SIZE * 2))) + START_SIZE;

    for (size_t i = 0; i < START_SIZE; i++) {
        this->_pos.push_back({player_startX * BLOCK_SIZE,
                              (player_startY + i) * BLOCK_SIZE});
    }
    this->createMap();
    this->spawnCandy();
};

void Nibbler::restart(void)
{
    size_t player_startX =
        (std::rand() % (this->_mapSize.x - (START_SIZE * 2))) + START_SIZE;
    size_t player_startY =
        (std::rand() % (this->_mapSize.y - (START_SIZE * 2))) + START_SIZE;
    this->_pos.clear();
    this->_map.clear();
    this->_current = Direction::UP;
    this->_next = Direction::UP;

    for (size_t i = 0; i < START_SIZE; i++) {
        this->_pos.push_back({player_startX * BLOCK_SIZE,
                              (player_startY + i) * BLOCK_SIZE});
    }
    this->createMap();
    this->spawnCandy();
};

void Nibbler::createMap(void)
{
    for (size_t y = 0; y < this->_mapSize.y; y++) {
        std::vector<size_t> temp;
        this->_map.push_back(temp);
        for (size_t x = 0; x < this->_mapSize.x; x++) {
            this->_map[y].push_back(0);
        }
    }
};

void Nibbler::spawnCandy(void)
{
    Pos test_rand;

    while (true) {
        test_rand.x = std::rand() % (this->_mapSize.x);
        test_rand.y = std::rand() % (this->_mapSize.y);
        if (this->_map[test_rand.y][test_rand.x] != 0)
            continue;
        if (std::find(_pos.begin(), _pos.end(), test_rand) != _pos.end()) {
            continue;
        }
        break;
    }
    this->_map[test_rand.y][test_rand.x] = 1;
    this->_candyPos = test_rand;
};

void Nibbler::movePlayer(Pos p_newPos)
{
    Pos last = this->_pos[0];
    Pos temp;

    this->_pos[0] = p_newPos;
    for (size_t i = 1; i < this->_pos.size(); i++) {
        temp = this->_pos[i];
        this->_pos[i] = last;
        last = temp;
    }
    if (p_newPos.x / BLOCK_SIZE == this->_candyPos.x &&
        p_newPos.y / BLOCK_SIZE == this->_candyPos.y) {
        this->_pos.push_back(last);
        this->_map[_candyPos.y][_candyPos.x] = 0;
        this->spawnCandy();
        this->_score += 100;
    }
};

bool Nibbler::goTo(Direction p_dir)
{
    static size_t goooo = 0;

    goooo++;
    if (goooo % 10 != 0)
        return (true);
    goooo = 0;
    if (!this->verifyEnd(p_dir))
        return (false);
    this->_current = p_dir;
    switch (p_dir)
    {
    case Direction::UP:
        this->movePlayer({this->_pos[0].x, this->_pos[0].y - BLOCK_SIZE});
        break;
    case Direction::DOWN:
        this->movePlayer({this->_pos[0].x, this->_pos[0].y + BLOCK_SIZE});
        break;
    case Direction::LEFT:
        this->movePlayer({this->_pos[0].x - BLOCK_SIZE, this->_pos[0].y});
        break;
    case Direction::RIGHT:
        this->movePlayer({this->_pos[0].x + BLOCK_SIZE, this->_pos[0].y});
        break;
    case Direction::UNDEFINED:
        break;
    };
    return (true);
};

bool Nibbler::verifyEnd(Direction p_dir)
{
    if ((this->_pos[0].x / BLOCK_SIZE <= 0 && p_dir == Direction::LEFT) ||
        (this->_pos[0].y / BLOCK_SIZE <= 0 && p_dir == Direction::UP) ||
        (this->_pos[0].x / BLOCK_SIZE >= this->_mapSize.x - 1 && p_dir == Direction::RIGHT) ||
        (this->_pos[0].y / BLOCK_SIZE >= this->_mapSize.y - 1 && p_dir == Direction::DOWN)) {
        return (false);
    }
    for (size_t i = 1; i < this->_pos.size(); i++) {
        if (this->_pos[0].x == this->_pos[i].x &&
            this->_pos[0].y == this->_pos[i].y)
            return (false);
    }
    return (true);
}

bool Nibbler::next_frame(KEYS p_ButtonPressed)
{
    Direction dir = static_cast<Direction>(p_ButtonPressed);

    if (static_cast<int>(p_ButtonPressed) > 3 ||
        (this->_current == Direction::UP && dir == Direction::DOWN) ||
        (this->_current == Direction::DOWN && dir == Direction::UP) ||
        (this->_current == Direction::LEFT && dir == Direction::RIGHT) ||
        (this->_current == Direction::RIGHT && dir == Direction::LEFT)) {
        return (this->goTo(this->_next));
    }
    this->_next = dir;
    return (this->goTo(this->_next));
};

}; // namespace Arcade
