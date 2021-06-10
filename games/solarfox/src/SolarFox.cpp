/*
** EPITECH PROJECT, 2019
** Game.cpp
** File description:
** player
*/

#include "SolarFox.hpp"

namespace Arcade
{

SolarFox::SolarFox(size_t p_width, size_t p_height) : IGame(p_width, p_height)
{
    this->_pos.push_back({this->_mapSize.x / 2 * BLOCK_SIZE,
                          this->_mapSize.y / 2 * BLOCK_SIZE});
    this->createMap();
    this->_ennemies.push_back(std::pair<Pos, Direction>({0, 0}, Direction::DOWN));
    this->_ennemies.push_back(std::pair<Pos, Direction>({0, (this->_mapSize.y - 1) * BLOCK_SIZE}, Direction::RIGHT));
    this->_ennemies.push_back(std::pair<Pos, Direction>({((this->_mapSize.x - 1) * BLOCK_SIZE), ((this->_mapSize.y - 1) * BLOCK_SIZE)}, Direction::UP));
    this->_ennemies.push_back(std::pair<Pos, Direction>({((this->_mapSize.x - 1) * BLOCK_SIZE), 0}, Direction::LEFT));
};

SolarFox::~SolarFox(void) {};

void SolarFox::createMap(void)
{
    for (size_t y = 0; y < this->_mapSize.y; y++) {
        std::vector<size_t> temp;
        this->_map.push_back(temp);
        for (size_t x = 0; x < this->_mapSize.x; x++) {
            this->_map[y].push_back(0);
            if (std::rand() % 5 == 0)
                this->_map[y][x] = 1;
            if (y < BORDER_SIZE || (this->_mapSize.y - (BORDER_SIZE + 1)) < y ||
                x < BORDER_SIZE || (this->_mapSize.x - (BORDER_SIZE + 1)) < x) {
                this->_map[y][x] = 2;
            }
        }
    }
};

void SolarFox::restart(void)
{
    this->_map.clear();
    this->_pos.clear();
    this->_ennemies.clear();
    this->_pos.push_back({this->_mapSize.x / 2 * BLOCK_SIZE,
                          this->_mapSize.y / 2 * BLOCK_SIZE});
    this->createMap();
    this->_ennemies.push_back(std::pair<Pos, Direction>({0, 0}, Direction::DOWN));
    this->_ennemies.push_back(std::pair<Pos, Direction>({0, (this->_mapSize.y - 1) * BLOCK_SIZE}, Direction::RIGHT));
    this->_ennemies.push_back(std::pair<Pos, Direction>({((this->_mapSize.x - 1) * BLOCK_SIZE), 0}, Direction::LEFT));
    this->_ennemies.push_back(std::pair<Pos, Direction>({((this->_mapSize.x - 1) * BLOCK_SIZE), ((this->_mapSize.y - 1) * BLOCK_SIZE)}, Direction::UP));
    this->_current = Direction::UNDEFINED;
    this->_next = Direction::UNDEFINED;
};

bool SolarFox::goTo(Direction p_dir)
{
    switch (p_dir) {
    case Direction::UP:
        this->_pos[0].y -= this->_speed;
        break;
    case Direction::DOWN:
        this->_pos[0].y += this->_speed;
        break;
    case Direction::LEFT:
        this->_pos[0].x -= this->_speed;
        break;
    case Direction::RIGHT:
        this->_pos[0].x += this->_speed;
        break;
    case Direction::UNDEFINED:
        break;
    }
    return (true);
};

void SolarFox::updateShot(KEYS p_ButtonPressed)
{
    Pos pos;
    Direction dir;
    int remaining;
    static int cd = 0;

    if (cd > 0)
        cd--;
    if (cd == 0 && p_ButtonPressed == KEYS::SPACE) {
        this->_shots.push_back(std::make_tuple(this->_pos[0], this->_current, SHOT_DURATION));
        cd = SHOT_CD;
    }
    for (size_t i = 0; i < this->_shots.size(); i++) {
        std::tie(pos, dir, remaining) = this->_shots[i];
        switch (dir) {
        case Direction::UP:
            pos.y -= this->_shotSpeed;
            break;
        case Direction::DOWN:
            pos.y += this->_shotSpeed;
            break;
        case Direction::LEFT:
            pos.x -= this->_shotSpeed;
            break;
        case Direction::RIGHT:
            pos.x += this->_shotSpeed;
            break;
        default:
            break;
        }
        this->_shots.erase(this->_shots.begin() + i);
        if (remaining > 0) {
            this->_shots.push_back(std::make_tuple(pos, dir, remaining - 1));
        }
        for (size_t y = 0; y < this->_map.size(); y++) {
            for (size_t x = 0; x < this->_map[y].size(); x++) {
                if (this->_map[y][x] == 1 &&
                    x * BLOCK_SIZE <= pos.x && pos.x < x * BLOCK_SIZE + BLOCK_SIZE &&
                    y * BLOCK_SIZE <= pos.y && pos.y < y * BLOCK_SIZE + BLOCK_SIZE) {
                    this->_map[y][x] = 0;
                    this->_score += 10;
                }
            }
        }
    }
};

void SolarFox::updateEnnemies(void)
{
    for (size_t i = 0; i < this->_ennemies.size(); i++) {
        switch (this->_ennemies[i].second) {
        case Direction::UP:
            this->_ennemies[i].first.y -= ENNEMY_SPEED;
            if (this->_ennemies[i].first.y <= 0)
                this->_ennemies[i].second = Direction::DOWN;
            break;
        case Direction::DOWN:
            this->_ennemies[i].first.y += ENNEMY_SPEED;
            if ((this->_mapSize.y - 1) * BLOCK_SIZE <= this->_ennemies[i].first.y)
                this->_ennemies[i].second = Direction::UP;
            break;
        case Direction::LEFT:
            this->_ennemies[i].first.x -= ENNEMY_SPEED;
            if (this->_ennemies[i].first.x <= 0)
                this->_ennemies[i].second = Direction::RIGHT;
            break;
        case Direction::RIGHT:
            this->_ennemies[i].first.x += ENNEMY_SPEED;
            if ((this->_mapSize.x - 1) * BLOCK_SIZE <= this->_ennemies[i].first.x)
                this->_ennemies[i].second = Direction::LEFT;
            break;
        default:
            break;
        }
    }
};

void SolarFox::ennemiesShot(void)
{
    for (size_t i = 0; i < this->_ennemies.size(); i++) {
        if (std::rand() % 12 == 0 &&
            this->_ennemies[i].first.x % BLOCK_SIZE == 0 &&
            this->_ennemies[i].first.y % BLOCK_SIZE == 0) {
            if (this->_ennemies[i].second == Direction::DOWN)
                this->_ennemiesShots.push_back(std::pair<Pos, Direction>(this->_ennemies[i].first, Direction::RIGHT));
            if (this->_ennemies[i].second == Direction::RIGHT)
                this->_ennemiesShots.push_back(std::pair<Pos, Direction>(this->_ennemies[i].first, Direction::UP));
            if (this->_ennemies[i].second == Direction::UP)
                this->_ennemiesShots.push_back(std::pair<Pos, Direction>(this->_ennemies[i].first, Direction::LEFT));
            if (this->_ennemies[i].second == Direction::LEFT)
                this->_ennemiesShots.push_back(std::pair<Pos, Direction>(this->_ennemies[i].first, Direction::DOWN));
        }
    }
    for (size_t i = 0; i < this->_ennemiesShots.size(); i++) {
        switch (this->_ennemiesShots[i].second) {
        case Direction::UP:
            this->_ennemiesShots[i].first.y -= ENNEMY_SHOT_SPEED;
            break;
        case Direction::DOWN:
            this->_ennemiesShots[i].first.y += ENNEMY_SHOT_SPEED;
            break;
        case Direction::LEFT:
            this->_ennemiesShots[i].first.x -= ENNEMY_SHOT_SPEED;
            break;
        case Direction::RIGHT:
            this->_ennemiesShots[i].first.x += ENNEMY_SHOT_SPEED;
            break;
        default:
            break;
        }
    }
};

bool SolarFox::next_frame(KEYS p_ButtonPressed)
{
    int button = static_cast<int>(p_ButtonPressed);

    if (button < 4) {
        this->_next = static_cast<Direction>(p_ButtonPressed);
    } if (this->_pos[0].x % BLOCK_SIZE == 0 && this->_pos[0].y % BLOCK_SIZE == 0
          && button < 4) {
        this->_current = static_cast<Direction>(p_ButtonPressed);
    } else if (this->_pos[0].x % BLOCK_SIZE == 0 && this->_pos[0].y % BLOCK_SIZE == 0) {
        if (this->_next != Direction::UNDEFINED &&
            ((this->_current == Direction::DOWN && this->_next != Direction::UP) ||
            (this->_current == Direction::UP && this->_next != Direction::DOWN) ||
            (this->_current == Direction::RIGHT && this->_next != Direction::LEFT) ||
            (this->_current == Direction::LEFT && this->_next != Direction::RIGHT))) {
            this->_current = this->_next;
        }
        this->_next = Direction::UNDEFINED;
    }
    if (this->_current != Direction::UNDEFINED) {
        this->updateShot(p_ButtonPressed);
        this->updateEnnemies();
        this->ennemiesShot();
    }
    return (this->goTo(this->_current));
};

}; // namespace Arcade
