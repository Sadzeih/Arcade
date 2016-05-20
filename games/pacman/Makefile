##
## Makefile for arcade in /home/devos-f/Documents/Projet/cpp_arcade/games/pacman/
##
## Made by François Devos
## Login   <devos_f@epitech.eu>
##
## Started on  Wed Mar 30 18:37:31 2016 François Devos
## Last update Thu Mar 31 15:24:08 2016 Alexis Guerville
##

CC				= g++

NAME			= ../lib_arcade_pacman.so

RM				= rm -rf

SRC				=	src/Pacman.cpp \
						src/Map.cpp \
						src/Ghost.cpp \
						src/Character.cpp \
						src/Exception.cpp

CXXFLAGS 	=  -fPIC -shared
CXXFLAGS	+=	-Wall
CXXFLAGS	+=	-Werror
CXXFLAGS	+=	-Wextra
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-I./include

ifeq			($(DEBUG), yes)
CXXFLAGS	+=	-g
endif

all:			$(NAME)

$(NAME):
					$(CC) $(CXXFLAGS) $(SRC) $(LDXXFLAGS) -o $(NAME)

clean:
					$(RM) $(OBJ)

fclean:		clean
					$(RM) $(NAME)

re:				fclean all
