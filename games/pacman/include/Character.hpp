//
// Character.hpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/games/pacman/include/
//
// Made by François Devos
// Login   <devos_f@epitech.eu>
//
// Started on  Wed Mar 30 18:09:36 2016 François Devos
// Last update Sat Apr  2 22:02:45 2016 Alexis Guerville
//

#ifndef _CHARACTER_HPP_
# define _CHARACTER_HPP_

#include <vector>
#include <iterator>
#include "Map.hpp"

class Character
{
public:
	enum Direction
	{
		UP		= 7,
		DOWN		= 8,
		LEFT		= 9,
		RIGHT		= 10,
		FORWARD	= 0
	};
	Character(Map *map);
	~Character();

	void weaken();
	bool grow();

	virtual bool move(Direction where);
	bool moveRight();
	bool moveLeft();
	bool moveDown();
	bool moveUp();

	bool genNext();

	virtual bool makeMove();

	bool checkOK();
	bool getWeak();
	int *getPosition();
	int *getNext();
	Direction getDirection();

protected:
	Map *_map;
	int *_position;
	int *_next;
	bool _weak;
	Direction _direction;
};

#endif
