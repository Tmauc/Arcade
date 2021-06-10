/*
** EPITECH PROJECT, 2019
** Core.cpp
** File description:
** Core.cpp
*/

#include "Core.hpp"

namespace Arcade
{

Core::Core(const std::string p_startingLib)
{
    struct timeval time;

    gettimeofday(&time,NULL);
    std::srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
    for (size_t i = 0; i < trustedLibs.size(); i++) {
        if (trustedLibs[i] == p_startingLib ||
            "lib/" + trustedLibs[i] == p_startingLib) {
            this->_currentLib = static_cast<int>(i);
        }
    }
    this->update_game(DEFAULT_GAME);
    this->update_lib(p_startingLib);
    this->launch_app();
}

Core::~Core(void)
{
}

void Core::next_library(void)
{
    this->_currentLib += 1;
    if (this->_currentLib == static_cast<int>(trustedLibs.size()))
        this->_currentLib = 0;
    this->update_lib("lib/" + trustedLibs[this->_currentLib]);
};

void Core::prev_library(void)
{
    this->_currentLib -= 1;
    if (this->_currentLib == -1)
        this->_currentLib = static_cast<int>(trustedLibs.size() - 1);
    this->update_lib("lib/" + trustedLibs[this->_currentLib]);
};

void Core::next_game(void)
{
    this->_currentGame += 1;
    if (this->_currentGame == static_cast<int>(trustedGames.size()))
        this->_currentGame = 0;
    this->update_game("games/" + trustedGames[this->_currentGame]);
};

void Core::prev_game(void)
{
    this->_currentGame -= 1;
    if (this->_currentGame == -1)
        this->_currentGame = static_cast<int>(trustedGames.size() - 1);
    this->update_game("games/" + trustedGames[this->_currentGame]);
};

KEYS Core::get_key(void)
{
    KEYS pressed = _lib->get_key();

    if (this->_done == 2) {
        switch (pressed)
        {
        case KEYS::RESTART:
            this->_game->restart();
            return (KEYS::RESTART);
        case KEYS::EXIT:
            if (this->_inGame == true)
                this->_done = 3;
            else
                this->_done = 4;
            this->_inGame = true;
            return (KEYS::NO_KEY);
        case KEYS::MENU:
            this->_inGame = false;
            return (KEYS::NO_KEY);
        case KEYS::NEXT_LIB:
            this->next_library();
            return (KEYS::NO_KEY);
        case KEYS::PREV_LIB:
            this->prev_library();
            return (KEYS::NO_KEY);
        case KEYS::NEXT_GAME:
            this->next_game();
            return (KEYS::NO_KEY);
        case KEYS::PREV_GAME:
            this->prev_game();
            return (KEYS::NO_KEY);
        case KEYS::ONE:
            this->_currentGame = 0;
            this->update_game("games/" + trustedGames[this->_currentGame]);
            return (KEYS::NO_KEY);
        case KEYS::TWO:
            this->_currentGame = 1;
            this->update_game("games/" + trustedGames[this->_currentGame]);
            return (KEYS::NO_KEY);
        case KEYS::THREE:
            this->_currentLib = 0;
            this->update_lib("lib/" + trustedLibs[this->_currentLib]);
            return (KEYS::NO_KEY);
        case KEYS::FOUR:
            this->_currentLib = 1;
            this->update_lib("lib/" + trustedLibs[this->_currentLib]);
            return (KEYS::NO_KEY);
        case KEYS::FIVE:
            this->_currentLib = 2;
            this->update_lib("lib/" + trustedLibs[this->_currentLib]);
            return (KEYS::NO_KEY);
        default:
            return (pressed);
        };
    } else {
        switch (pressed)
        {
        case KEYS::EXIT:
            this->_done = 4;
            this->_inGame = true;
            return (KEYS::NO_KEY);
        case KEYS::RESTART:
            this->_done = 2;
            return (KEYS::RESTART);
        case KEYS::NEXT_LIB:
            return ((KEYS)108);
        case KEYS::PREV_LIB:
            return ((KEYS)107);
        case KEYS::NEXT_GAME:
            return ((KEYS)112);
        case KEYS::PREV_GAME:
            return ((KEYS)111);
        default:
            return (pressed);
        }
    }
};

void Core::update_game(const std::string p_newGame)
{
    if (this->_gameHandler != NULL) {
        dlclose(this->_gameHandler);
    }
    this->_gameHandler = dlopen(p_newGame.c_str(), RTLD_LAZY);
    if (this->_gameHandler == NULL) {
        std::cout << "ERROR : [" << dlerror() << "]" << std::endl;
        exit(84);
    }
    this->_game = getSoClass<IGame>(this->_gameHandler, "newGame");
    if (this->_game == NULL) {
        throw;
    }
};

void Core::update_lib(const std::string p_newLib)
{
    if (this->_lib != NULL) {
        this->_lib->close_window();
    }
    if (this->_libHandler != NULL) {
        dlclose(this->_libHandler);
    }
    this->_libHandler = dlopen(p_newLib.c_str(), RTLD_LAZY);
    if (this->_libHandler == NULL) {
        std::cout << "ERROR : [" << dlerror() << "]" << std::endl;
        exit(84);
    }
    this->_lib = getSoClass<ILib>(this->_libHandler, "newLib");
    if (this->_lib == NULL) {
        throw;
    }
};

void Core::draw_score(void)
{
    size_t i = 1;
    std::string score;
    std::ifstream inFile;
    std::string path;

    if (this->_currentGame == 0)
        path = "Ressource/score/score_nibbler.txt";
    else if (this->_currentGame == 1)
        path = "Ressource/score/score_solarfox.txt";
    inFile.open(path);
    if (!inFile)
        return;
    for (; inFile >> score; i++) {
        _lib->draw_text(score, {128, 128, 128, 255}, {820, i * 30}, 20);
    }
    inFile.close();
}

void Core::draw_menu(KEYS button)
{
    Color color_m = {128, 128, 128, 255};
    _lib->draw_text("Arcade", color_m, {250, 10}, 150);
    _lib->draw_text("1. Nibbler", color_m, {200, 190}, 50);
    _lib->draw_text("2. SolarFox", color_m, {200, 250}, 50);
    _lib->draw_text("3. SDL2", color_m, {550, 190}, 50);
    _lib->draw_text("4. Sfml", color_m, {550, 250}, 50);
    _lib->draw_text("5. Ncurse", color_m, {550, 310}, 50);
    _lib->draw_text("Press enter for launch the game", color_m, {500, 470}, 30);
    _lib->draw_text("Username: "+_username, {128, 128, 128, 255}, {40, 480}, 20);
    draw_score();
    if (this->_currentGame == 0)
        _lib->draw_text("> Nibbler <", color_m, {200, 390}, 50);
    else if (this->_currentGame == 1)
        _lib->draw_text("> SolarFox <", color_m, {200, 390}, 50);
    if (this->_currentLib == 0)
        _lib->draw_text("> SDL2 <", color_m, {550, 390}, 50);
    if (this->_currentLib == 1)
        _lib->draw_text("> Sfml <", color_m, {550, 390}, 50);
    if (this->_currentLib == 2)
        _lib->draw_text("> Ncurse <", color_m, {550, 390}, 50);
    if (button == KEYS::RESTART) {
        this->_inGame = true;
        this->_lib->clear();
    }
};

void Core::wait(void)
{
    std::clock_t c_start = std::clock();
    static auto t_start = std::chrono::high_resolution_clock::now();
    auto t_end = std::chrono::high_resolution_clock::now();    
    double time = 16 - std::chrono::duration<double, std::milli>(t_end - t_start).count();

    (void)c_start;
    if (time > 0)
        usleep(time * 1000);
    t_start = std::chrono::high_resolution_clock::now();
};

void Core::draw_game(void)
{
    std::vector<Pos> pos = _game->getPlayerPos();
    std::vector<std::pair<Pos, Direction>> ennemies = _game->getEnnemiesPos();
    std::vector<std::pair<Pos, Direction>> enshot = _game->getEnnemiesShot();
    std::string score = "Score: " + std::to_string(_game->getScore());
    std::vector<std::tuple<Pos, Direction, int>> shots = _game->getShotPos();

    for (size_t y = 0; y < this->_game->size().y; y++) {
        for (size_t x = 0; x < this->_game->size().x; x++) {
            this->_lib->draw_block(x * BLOCK_SIZE, y * BLOCK_SIZE,
                                   this->_game[0][y][x]);
        }
    }
    for (size_t i = 0; i < pos.size(); i++) {
        this->_lib->draw_block(pos[i].x, pos[i].y, 3);
    }
    _lib->draw_text(score, {255, 0, 0, 255}, {10, 10}, 50);
    _lib->draw_text("Username: "+_username, {128, 128, 128, 255}, {10, 60}, 30);
    for (size_t i = 0; i < shots.size(); i++) {
        if (std::get<1>(shots[i]) == Direction::RIGHT ||
            std::get<1>(shots[i]) == Direction::LEFT) {
            this->_lib->draw_block(std::get<0>(shots[i]).x, std::get<0>(shots[i]).y, 4);
        } else {
            this->_lib->draw_block(std::get<0>(shots[i]).x, std::get<0>(shots[i]).y, 5);
        }
    }
    for (size_t i = 0; i < ennemies.size(); i++) {
        this->_lib->draw_block(ennemies[i].first.x, ennemies[i].first.y, 6);
    }
    for (size_t i = 0; i < enshot.size(); i++) {
        this->_lib->draw_block(enshot[i].first.x, enshot[i].first.y, 7);
    }
};

void Core::getUsername(void)
{
    KEYS button;

    while (this->_done == 1) {
        button = this->get_key();
        if ((int)button != 12 && (int)button != -1 && (int)button != 11) {
            if ((int)button == 8)
                _username = _username.substr(0, _username.length() - 1);
            else
                _username += (char)button;
        }
        _lib->draw_text("Arcade", {128, 128, 128, 255}, {250, 10}, 150);
        _lib->draw_text("Username: "+_username, {128, 128, 128, 255}, {100, 300}, 50);
        this->_lib->update();
    }
    this->_lib->clear();
}

void Core::stock_score(void)
{
    std::ifstream ss;
    std::vector<std::string> list;
    std::string rdr;
    std::string path;
    std::ofstream fout;
    std::string na_sc = _username + std::to_string(this->_game->getScore());

    if (this->_currentGame == 0)
        path = "Ressource/score/score_nibbler.txt";
    else if (this->_currentGame == 1)
        path = "Ressource/score/score_solarfox.txt";
    ss.open(path);
    if (ss) {
        while (ss >> rdr) {
            list.push_back(rdr);
        }
        ss.close();
    }
    fout.open(path);
    list.push_back(na_sc);
    for (size_t i = 0; i < list.size(); i++) {
        fout << list[i] << "\n";
    }
    fout.close();
}

void Core::launch_app(void)
{
    KEYS button;
    
    this->getUsername();
    while (this->_done == 2) {
        button = this->get_key();
        if (this->_inGame == false)
            this->draw_menu(button);
        else {
            if (!this->_game->next_frame(button)) {
                this->_lib->close_window();
                this->stock_score();
                return;
            }
            this->draw_game();
        }
        this->_lib->update();
        this->wait();
    }
    this->_lib->close_window();
    if (this->_done == 3)
        this->stock_score();
};

}; // namespace Arcade
