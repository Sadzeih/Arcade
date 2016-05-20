##
## Makefile for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/lib/OpenGL/
##
## Made by Alexis Guerville
## Login   <guervi_a@epitech.eu>
##
## Started on  Thu Mar 10 14:08:51 2016 Alexis Guerville
## Last update Fri Apr  1 22:00:31 2016 Alexis Guerville
##

CC				= g++ -fPIC -shared

NAME			= ../lib_arcade_opengl.so

RM				= rm -rf

SRC				=	src/GLLib.cpp \
						src/Exception.cpp \
						src/Shader.cpp

CXXFLAGS	=	-Wall
CXXFLAGS	+=	-Werror
CXXFLAGS	+=	-Wextra
CXXFLAGS	+=	-I./include
CXXFLAGS	+=	-std=c++11

ifeq					($(DEBUG), yes)
CXXFLAGS	+=	-g
endif

LDXXFLAGS	+=	-L./lib -lGLEW -lsfml-window -lsfml-graphics -lGL

all:			$(NAME)

$(NAME):
					$(CC) $(CXXFLAGS) $(SRC) $(LDXXFLAGS) -o $(NAME)

clean:
					$(RM) $(OBJ)

fclean:		clean
					$(RM) $(NAME)

re:				fclean all
