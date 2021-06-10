/*
** EPITECH PROJECT, 2019
** Core.hpp
** File description:
** Core.hpp
*/

#pragma once

#include <sys/time.h>
#include <iostream>
#include <dlfcn.h>
#include <algorithm>
#include <unistd.h>
#include <strings.h>

#include "Arcade.hpp"
#include "IGame.hpp"
#include "ILib.hpp"

namespace Arcade
{

class Core
{
private:
    int _currentGame = 0;
    int _currentLib;
    IGame *_game = NULL;
    ILib *_lib = NULL;
    std::string _username = "";
    int _done = true;
    bool _inGame = false;
    void *_libHandler = NULL;
    void *_gameHandler = NULL;

    void wait(void);
    void next_library(void);
    void prev_library(void);
    void next_game(void);
    void prev_game(void);
    
public:
    Core(const std::string p_startingLib);
    ~Core();

    void launch_app(void);
    KEYS get_key(void);
    
    void update_game(const std::string p_newGame);
    void update_lib(const std::string p_newLib);

    void draw_menu(KEYS button);
    void draw_game(void);
    void draw_map(void);
    void draw_player(void);
    void getUsername(void);
    void stock_score(void);
    void draw_score(void);
};

template <class T>
T* getSoClass(void *p_handle, std::string p_classFuncName)
{
    T* (*fnc)();

    fnc = reinterpret_cast<T *(*)()>(dlsym(p_handle, p_classFuncName.c_str()));
    if (fnc == NULL)
        return (NULL);
    return (fnc());
}

}; // namespace Arcade
