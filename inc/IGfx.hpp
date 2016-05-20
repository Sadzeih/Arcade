//
// IGfx.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/lib/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 13:29:26 2016 Alexis Guerville
// Last update Fri Apr  1 13:43:45 2016 Alexis Guerville
//

#ifndef IGFX_HPP_
#define IGFX_HPP_

#include <string>
#include <ctime>
#include <map>

class IGfx
{
public:
	enum Command
	{
		QUIT = -1,
		NOTHING = 0,
		NEXT_GAME = 1,
		PREV_GAME = 2,
		NEXT_LIB = 3,
		PREV_LIB = 4,
		RESTART = 5,
		MENU = 6,
		UP = 7,
		DOWN = 8,
		LEFT = 9,
		RIGHT = 10
	};

	virtual ~IGfx() {}
	virtual void display(struct timeval&) = 0;
	virtual void clear() = 0;

	virtual void drawCase(int width, int height, int, int) = 0;
	virtual void drawWall(int width, int height, int, int) = 0;
	virtual void drawItem(int width, int height, int, int) = 0;
	virtual void drawCharacter(int, int, int, int, std::string const) = 0;
	virtual void drawPastille(int, int, int, int) = 0;
	virtual int getEvent() = 0;
	virtual int menu() = 0;
	virtual double getTimeDiff(struct timeval pTime) const = 0;
	virtual void getTime(struct timeval *pTime) const = 0;
};

#endif
