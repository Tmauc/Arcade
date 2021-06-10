/*
** EPITECH PROJECT, 2019
** Gtk.cpp
** File description:
** gtk+ cpp file
*/

#include "Sfml.hpp"

namespace Arcade
{

Sfml::Sfml(void): ILib(), _app(sf::VideoMode(WIDTH, HEIGHT), "ARCADE SFML", sf::Style::Close)
{
    if (!_font.loadFromFile("Ressource/fonts/Roboto-Light.ttf")) {
        std::cout << "AH LA FONT!!" << std::endl;
    }
    _app.isOpen();
    _app.clear(sf::Color(20, 20, 20));
    this->_texture.loadFromFile(BLOCK_PATH);
};

Sfml::~Sfml(void)
{
};

KEYS Sfml::get_key(void)
{
    sf::Event event;
    
    while (this->_app.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            return (KEYS::EXIT);
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::Up:
                return (KEYS::UP);
            case sf::Keyboard::Down:
                return (KEYS::DOWN);
            case sf::Keyboard::Left:
                return (KEYS::LEFT);
            case sf::Keyboard::Right:
                return (KEYS::RIGHT);
            case sf::Keyboard::L:
                return (KEYS::NEXT_LIB);
            case sf::Keyboard::K:
                return (KEYS::PREV_LIB);
            case sf::Keyboard::P:
                return (KEYS::NEXT_GAME);
            case sf::Keyboard::O:
                return (KEYS::PREV_GAME);
            case sf::Keyboard::Return:
                return (KEYS::RESTART);
            case sf::Keyboard::Escape:
                return (KEYS::MENU);
            case sf::Keyboard::Num1:
                return (KEYS::ONE);
            case sf::Keyboard::Num2:
                return (KEYS::TWO);
            case sf::Keyboard::Num3:
                return (KEYS::THREE);
            case sf::Keyboard::Num4:
                return (KEYS::FOUR);
            case sf::Keyboard::Num5:
                return (KEYS::FIVE);
            case sf::Keyboard::Space:
                return (KEYS::SPACE);
            };
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode != 111 &&
            event.text.unicode != 112 &&
            event.text.unicode != 107 &&
            event.text.unicode != 108 &&
            event.text.unicode != 49 &&
            event.text.unicode != 50 &&
            event.text.unicode != 51 &&
            event.text.unicode != 52)
                return ((KEYS)event.text.unicode);
        }   
    }
    return (KEYS::NO_KEY);
};

void Sfml::draw_text(std::string p_str, Color p_color, Pos p_where, size_t p_size)
{
    sf::Text txt;
    sf::Color color(p_color.r, p_color.g, p_color.b, p_color.a);

    txt.setString(p_str);
    txt.setFont(this->_font);
    txt.setCharacterSize(p_size);
    txt.setFillColor(color);
    txt.setPosition(p_where.x, p_where.y);
    _app.draw(txt);
};

void Sfml::draw_block(int p_x, int p_y, int p_id)
{
    sf::Sprite sprite;

    sprite.setTexture(this->_texture);
    sprite.setTextureRect(sf::IntRect(BLOCK_SIZE * p_id, 0, BLOCK_SIZE, BLOCK_SIZE));
    sprite.setPosition(p_x, p_y);
    _app.draw(sprite);
}

void Sfml::update(void)
{
    _app.display();
    clear();
};

void Sfml::clear(void)
{
    _app.clear(sf::Color(0, 0, 0));
}

void Sfml::close_window(void)
{
    _app.close();
};
}; // namespace Arcade
