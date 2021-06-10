/*
** EPITECH PROJECT, 2019
** Gtk.cpp
** File description:
** gtk+ cpp file
*/

#include "Ncurse.hpp"

namespace Arcade
{

Ncurse::Ncurse(void): ILib()
{
    WINDOW *window = initscr();

    noecho();
    curs_set(0);
    nodelay(window, true);
    refresh();
    _window = window;
};

Ncurse::~Ncurse(void)
{
};

KEYS Ncurse::get_key(void)
{
    int ch = getch();
    
    switch (ch) {
        case ' ':
            return (KEYS::SPACE);
        case 'q':
            return (KEYS::EXIT);
        case 'A':
            return (KEYS::UP);
        case 'B':
            return (KEYS::DOWN);
        case 'D':
            return (KEYS::LEFT);
        case 'C':
            return (KEYS::RIGHT);
        case 'l':
            return (KEYS::NEXT_LIB);
        case 'k':
            return (KEYS::PREV_LIB);
        case 'p':
            return (KEYS::NEXT_GAME);
        case 'o':
            return (KEYS::PREV_GAME);
        case 10:
            return (KEYS::RESTART);
        case 'w':
            return (KEYS::MENU);
        case '1':
            return (KEYS::ONE);
        case '2':
            return (KEYS::TWO);
        case '3':
            return (KEYS::THREE);
        case '4':
            return (KEYS::FOUR);
        case '5':
            return (KEYS::FIVE);
        default:
            if (isalpha(ch))
                return ((KEYS)ch);
            break;
    }
    return (KEYS::NO_KEY);
};

void Ncurse::draw_text(std::string p_str, Color p_color, Pos p_where, size_t p_size)
{
    (void)p_color;
    (void)p_size;
    mvprintw(p_where.y / BLOCK_SIZE, p_where.x / BLOCK_SIZE, "%s", p_str.c_str());
};

void Ncurse::draw_block(int p_x, int p_y, int p_id)
{
    mvprintw(p_y / BLOCK_SIZE, p_x / BLOCK_SIZE, "%c", tab_ncurse[p_id]);
}

void Ncurse::update(void)
{
    int y = 0;
    int x = 0;

    for (; y < BASIC::HEIGHT / 20; y++) {
        for (x = 0; x < BASIC::WIDTH / 20; x++);
            mvprintw(y, x + 1, "%c", '|');
    }
    for (x = 0; x <= BASIC::WIDTH / 20; mvprintw(y, x + 1, "%c", '-'), x++);
    refresh();
};

void Ncurse::clear(void)
{
    wclear(_window);
}

void Ncurse::close_window(void)
{
    refresh();
    endwin();
};

}; // namespace Arcade
