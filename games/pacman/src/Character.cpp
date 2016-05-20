//
// Character.cpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/games/pacman/src/
//
// Made by François Devos
// Login   <devos_f@epitech.eu>
//
// Started on  Wed Mar 30 18:11:32 2016 François Devos
// Last update Sun Apr  3 02:21:24 2016 Alexis Guerville
//

#include <iostream>
#include <vector>
#include <iterator>
#include "Character.hpp"
#include "Map.hpp"

Character::Character(Map *map)
: _map(map)
{
	_weak = 1;
	_position = new int[2];
	_position[0] = 17;
	_position[1] = 19;
	_map->setTypeAtPos(_position[1], _position[0], Map::PLAYER);
	_next = new int[2];
	_next[0] = _position[0] - 1;
	_next[1] = _position[1];
	_direction = DOWN;
}

Character::~Character()
{
}

void Character::weaken()
{
	_weak = 1;
}

bool Character::grow()
{
	_weak = 0;
	return (true);
}

bool Character::makeMove()
{
	int *prev = new int[2];

	prev[0] = _position[0];
	prev[1] = _position[1];
	int type = _map->getTypeAtPos(_next[1], _next[0]);
	if ((type == Map::EVIL_DUDE || _map->getTypeAtPos(_next[1], _next[0]) == Map::EVIL_DUDE) && _weak == 1)
		return (false);
	_map->setTypeAtPos(prev[1], prev[0], Map::EMPTY);
	_position[0] = _next[0];
	_position[1] = _next[1];
	type = _map->getTypeAtPos(_position[1], _position[0]);
	if (_direction == RIGHT)
		_map->setTypeAtPos(_position[1], _position[0], Map::PACMAN_RIGHT);
	else if (_direction == DOWN)
		_map->setTypeAtPos(_position[1], _position[0], Map::PACMAN_DOWN);
	else if (_direction == UP)
		_map->setTypeAtPos(_position[1], _position[0], Map::PACMAN_UP);
	if (_direction == LEFT)
		_map->setTypeAtPos(_position[1], _position[0], Map::PACMAN_LEFT);
	if (type == Map::POWERUP)
	{
		if (grow() == false)
			return false;
	}
	return genNext();
}

bool Character::genNext()
{
	if (_direction == UP)
	{
		if (_position[0] == 0)
			return false;
		if (_map->getTypeAtPos(_position[1], _position[0] - 1) != Map::BLOCK)
		{
			_next[0] = _position[0] - 1;
			_next[1] = _position[1];
		}
	}
	else if (_direction == DOWN)
	{
		if (_position[0] == 0)
			return false;
		if (_map->getTypeAtPos(_position[1], _position[0] + 1) != Map::BLOCK)
		{
			_next[0] = _position[0] + 1;
			_next[1] = _position[1];
		}
	}
	else if (_direction == LEFT)
	{
		if (_position[1] == 0)
			return false;
		if (_map->getTypeAtPos(_position[1] - 1, _position[0]) != Map::BLOCK)
		{
			_next[0] = _position[0];
			_next[1] = _position[1] - 1;
		}
	}
	else if (_direction == RIGHT)
	{
		if (_position[1] == 0)
			return false;
		if (_map->getTypeAtPos(_position[1] + 1, _position[0]) != Map::BLOCK)
		{
			_next[0] = _position[0];
			_next[1] = _position[1] + 1;
		}
	}
	return true;
}

bool Character::move(Direction where)
{
	if (where == UP)
	{
		if (moveUp() == false)
			return false;
	}
	else if (where == DOWN)
	{
		if (moveDown() == false)
			return false;
	}
	else if (where == RIGHT)
	{
		if (moveRight() == false)
			return false;
	}
	else if (where == LEFT)
	{
		if (moveLeft() == false)
			return false;
	}
	return makeMove();
}


bool Character::moveUp()
{
	_direction = UP;
	_next[0] = _position[0] - 1;
	_next[1] = _position[1];
	return checkOK();
}

bool Character::moveDown()
{
	_direction = DOWN;
	_next[0] = _position[0] + 1;
	_next[1] = _position[1];
	return checkOK();
}

bool Character::moveLeft()
{
	_direction = LEFT;
	_next[0] = _position[0];
	_next[1] = _position[1] - 1;
	return checkOK();
}

bool Character::moveRight()
{
	_next[0] = _position[0];
	_next[1] = _position[1] + 1;
	_direction = RIGHT;
	return checkOK();
}

bool Character::checkOK()
{
	if (_map->getTypeAtPos(_next[1], _next[0]) == Map::BLOCK)
	{
		_next[0] = _position[0];
		_next[1] = _position[1];
	}
	return true;
}

int * Character::getPosition()
{
	return (_position);
}

bool	Character::getWeak()
{
	return (_weak);
}

int * Character::getNext()
{
	return (_next);
}

Character::Direction Character::getDirection()
{
	return (_direction);
}
