##
## Makefile for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/lib/OpenGL/
##
## Made by Alexis Guerville
## Login   <guervi_a@epitech.eu>
##
## Started on  Thu Mar 10 14:08:51 2016 Alexis Guerville
## Last update Thu Mar 31 15:23:18 2016 Alexis Guerville
##

CC				= g++

NAME			= ../lib_arcade_snake.so

RM				= rm -rf

SRC				=	src/Snake.cpp \
						src/Map.cpp \
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
