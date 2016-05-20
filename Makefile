##
## Makefile for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/
##
## Made by Alexis Guerville
## Login   <guervi_a@epitech.eu>
##
## Started on  Thu Mar 10 12:58:17 2016 Alexis Guerville
## Last update Thu Mar 31 15:27:00 2016 Alexis Guerville
##

CC				= g++

RM				= rm -f

NAME			=	arcade

CXXFLAGS		=	-I./inc
CXXFLAGS		+= -Wall
CXXFLAGS		+= -Wextra
CXXFLAGS		+= -std=c++11

ifeq				($(DEBUG), yes)
CXXFLAGS		+= -g
endif

LDFLAGS		=	-ldl

SRC				= src/main.cpp \
						src/Exception.cpp \
						src/Core.cpp \
						src/Map.cpp

OBJ				= $(SRC:.cpp=.o)

all:			$(NAME)

opengl:
					cd lib/OpenGL && $(MAKE) re DEBUG=$(DEBUG)

caca:
					cd lib/libcaca && $(MAKE) re DEBUG=$(DEBUG)

sdl:
					cd lib/SDL && $(MAKE) re DEBUG=$(DEBUG)

snake:
					cd games/snake && $(MAKE) re DEBUG=$(DEBUG)

pacman:
					cd games/pacman && $(MAKE) re DEBUG=$(DEBUG)

$(NAME):	$(OBJ)
						cd lib/OpenGL && $(MAKE)
						cd lib/libcaca && $(MAKE)
	      		cd lib/SDL && $(MAKE)
						cd games/snake && $(MAKE)
						cd games/pacman && $(MAKE)
						$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
					cd lib/OpenGL && $(MAKE) clean
					cd lib/libcaca && $(MAKE) clean
	      	cd lib/SDL && $(MAKE) clean
					cd games/snake && $(MAKE) clean
					cd games/pacman && $(MAKE) clean
					$(RM) $(OBJ)

fclean:		clean
					cd lib/OpenGL && $(MAKE) fclean
					cd lib/libcaca && $(MAKE) fclean
					cd lib/SDL && $(MAKE) fclean
					cd games/snake && $(MAKE) fclean
					cd games/pacman && $(MAKE) fclean
					$(RM) $(NAME)

re:				opengl snake caca sdl pacman fclean all
