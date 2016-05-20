##
## Makefile for arcade in /home/devos-f/Documents/Projet/cpp_arcade/lib/libcaca
##
## Made by François Devos
## Login   <devos-f@epitech.net>
##
## Started on  Fri Mar 11 11:19:22 2016 François Devos
## Last update Wed Mar 30 18:30:53 2016 François Devos
##

CC	= g++ -fPIC -shared -g

NAME	= ../lib_arcade_libcaca.so

RM	= rm -rf

SRC	= cacaLib.cpp \
	Exception.cpp

CXXFLAGS = -Wall
CXXFLAGS += -Werror
CXXFLAGS += -Wextra
CXXFLAGS += -I./include

LDXXFLAGS += -L./lib -lcaca

all:	$(NAME)

$(NAME):
	$(CC) $(CXXFLAGS) $(SRC) $(LDXXFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
