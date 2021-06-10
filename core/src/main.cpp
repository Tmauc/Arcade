/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** main file
*/

#include "Core.hpp"

void print_help(const std::string p_binary_name = "./arcade")
{
    std::cout << "USAGE :" << std::endl
              << "        " << p_binary_name << " [LIB_PATH.so]" << std::endl;
}

int launch_arcade(const std::string p_lib)
{
    const char *temp_index = rindex(p_lib.c_str(), '/');

    if (temp_index != NULL) {
        if (std::find(Arcade::trustedLibs.begin(), Arcade::trustedLibs.end(),
                      std::string(&temp_index[1])) == Arcade::trustedLibs.end()) { 
            return (84);
        }
    } else {
        if (std::find(Arcade::trustedLibs.begin(), Arcade::trustedLibs.end(),
                      p_lib) == Arcade::trustedLibs.end()) {
            return (84);
        }
    }
    Arcade::Core arcade(p_lib);
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        print_help(av[0]);
        return (84);
    }
    return (launch_arcade(av[1]));
}
