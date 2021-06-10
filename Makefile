##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile
##

.PHONY: all core games graphicals clean fclean re

all: core games graphicals

core:
	make -C core/ all

games:
	make -C games/ all

graphicals:
	make -C lib/ all

clean:
	make -C core/ clean
	make -C games/ clean
	make -C lib/ clean

fclean:
	make -C core/ fclean
	make -C games/ fclean
	make -C lib/ fclean

re:
	make -C core/ re
	make -C games/ re
	make -C lib/ re
