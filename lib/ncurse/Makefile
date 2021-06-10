##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile
##

NAME		=	lib_arcade_ncurse.so

CC		=	g++

NCURSELIBS	=	-lncurses

CFLAGS		+=	-g -Iinc -fPIC -W -Wextra

LDFLAGS		+=	 -shared -fdiagnostics-color=always $(NCURSELIBS)

FILES		=	src/Ncurse.cpp		\

SRCS		=	$(FILES)

OBJ		=	$(SRCS:.cpp=.o)

.PHONY: fclean clean all re debug

RED		=	\033[0;31m
GREEN		=	\033[0;32m
NC		=	\033[0m
GREY		=	\033[90m
BG_COLOR	=	\033[46m

all:			$(NAME)

$(NAME):	$(OBJ)
	@echo -e '${BG_COLOR}Flags: $(LDFLAGS) $(CPPFLAGS)${NC}'
	@echo -e '${GREEN}Create${NC}: ${GREY}./$(NAME)${NC}'
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LDFLAGS)
	@ln -s ncurse/$(NAME) ../$(NAME)

%.o:		%.cpp
	@echo -e '${GREEN} [ OK ]${NC} Building : $<'
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)


clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_T)
	@rm -rf vgcore.*
	@rm -f gmon.out
	@rm -rf a.out
	@find . -name *.gc* -delete
	@echo -e '${RED}Clean${NC} : OK'

fclean:		clean
	@rm -rf $(NAME)
	@echo -e '${RED}Fclean${NC}: ./$(NAME) removed'
	@rm -rf ../$(NAME)

re:		fclean all
