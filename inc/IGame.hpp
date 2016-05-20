//
// IGame.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/inc/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Fri Mar 11 13:52:02 2016 Alexis Guerville
// Last update Fri Apr  1 13:46:52 2016 Alexis Guerville
//

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "Map.hpp"

class IGame
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
	virtual ~IGame() {}

	virtual Map *getMap() const = 0;
	virtual void generateMap() const = 0;
	virtual void getTime(struct timeval*) const = 0;
	virtual double getTimeDiff(struct timeval) const = 0;
	virtual bool update(struct timeval&, int&) = 0;
};

#endif
