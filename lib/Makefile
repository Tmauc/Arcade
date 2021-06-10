##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile
##

.PHONY: all sfml SDL ncurse clean fclean re

all: sfml SDL ncurse

sfml:
	make -C sfml/ all

SDL:
	make -C SDL/ all

ncurse:
	make -C ncurse/ all

clean:
	make -C SDL/ clean
	make -C sfml/ clean
	make -C ncurse/ clean

fclean:
	make -C SDL/ fclean
	make -C sfml/ fclean
	make -C ncurse/ fclean

re:
	make -C SDL/ re
	make -C sfml/ re
	make -C ncurse/ re
