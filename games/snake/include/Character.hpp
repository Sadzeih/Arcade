//
// Character.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/games/snake/include/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Fri Mar 11 16:04:45 2016 Alexis Guerville
// Last update Fri Apr  1 13:49:00 2016 Alexis Guerville
//

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <vector>
#include <iterator>
#include "Map.hpp"

class Character
{
public:
	enum Direction
	{
		FORWARD	= 0,
		UP			= 7,
		DOWN		= 8,
		LEFT		= 9,
		RIGHT		= 10,
	};
	Character(Map *map);
	~Character();

	bool grow();

	bool move(Direction where);
	bool moveRight();
	bool moveLeft();
	bool moveDown();
	bool moveUp();

	bool genNext();

	bool makeMove();

	bool checkOK();

	std::vector<int *>getPosition();

private:
	Map *_map;
	std::vector<int *> _position;
	int *_next;
	Direction _direction;
};

#endif
