##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile
##

.PHONY: all nibbler solarfox pacman clean fclean re

all: nibbler solarfox pacman

nibbler:
	make -C nibbler/ all
	make -C solarfox/ all

clean:
	make -C nibbler/ clean
	make -C solarfox/ clean
	make -C pacman/ clean

fclean:
	make -C nibbler/ fclean
	make -C solarfox/ fclean
	make -C pacman/ fclean

re:
	make -C nibbler/ re
	make -C solarfox/ re
