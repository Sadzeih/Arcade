##
## Makefile for arcade in /home/thomas/rendu/tek2/C++/cpp_arcade/lib/SDL
##
## Made by raout_t
## Login   <thomas@epitech.net>
##
## Started on  Fri Mar 11 13:16:19 2016 raout_t
## Last update Tue Mar 29 18:45:25 2016 Alexis Guerville
##

CXX		=	g++

NAME		=	../lib_arcade_sdl.so

RM		=	rm -rf

SRC		=	SDLLib.cpp \
				Exception.cpp

CXXFLAGS	=	-Wall
CXXFLAGS	+=	-Wextra
CXXFLAGS	+=	-I include -I ../../inc
CXXFLAGS	+=	-fPIC

ifeq			($(DEBUG), yes)
CXXFLAGS	+=	-g
endif

LDFLAGS	+=	-L ./lib/ -shared
LDFLAGS	+=	-l SDL2 -l SDL2_image -lSDL2

OBJ	=	$(SRC:.cpp=.o)

all:			$(NAME)

$(NAME):	$(OBJ)
		$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
