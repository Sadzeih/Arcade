//
// Character.cpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/games/snake/src/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Fri Mar 11 16:15:31 2016 Alexis Guerville
// Last update Sat Apr  2 17:27:56 2016 Alexis Guerville
//

#include <iostream>
#include <vector>
#include <iterator>
#include "Character.hpp"
#include "Map.hpp"

Character::Character(Map *map)
: _map(map)
{
	for (int i = 0; i < 4; i++)
	{
		_position.push_back(new int[2]);
		_position[i][0] = _map->getHeight() / 2 + i;
		_position[i][1] = _map->getWidth() / 2;
		_map->setTypeAtPos(_position[i][1], _position[i][0], Map::PLAYER);
	}
	_next = new int[2];
	_next[0] = _position[0][0] - 1;
	_next[1] = _position[0][1];
	_direction = UP;
}

Character::~Character()
{
}

bool Character::grow()
{
	int *end;
	int *toadd = new int[2];
	std::vector<int *>::iterator it = _position.end();
	--it;
	end = *(it);
	if (_direction == UP)
	{
		toadd[0] = end[0] + 1;
		toadd[1] = end[1];
	}
	else if (_direction == DOWN)
	{
		toadd[0] = end[0] - 1;
		toadd[1] = end[1];
	}
	else if (_direction == RIGHT)
	{
		toadd[0] = end[0];
		toadd[1] = end[1] - 1;
	}
	else if (_direction == LEFT)
	{
		toadd[0] = end[0];
		toadd[1] = end[1] + 1;
	}
	if (_map->getTypeAtPos(toadd[1], toadd[0]) != Map::EMPTY)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (i != j && _map->getTypeAtPos(end[1] + i, end[0] + j) == Map::EMPTY)
				{
					toadd[0] = end[0] + j;
					toadd[1] = end[1] + i;
					_position.push_back(toadd);
					_map->setTypeAtPos(toadd[1], toadd[0], Map::PLAYER);
					return true;
				}
			}
		}
		return false;
	}
	_position.push_back(toadd);
	return true;
}

bool Character::makeMove()
{
	std::vector<int *>::iterator prev;
	std::vector<int *>::iterator it;

	it = _position.end();
	--it;
	_map->setTypeAtPos((*it)[1], (*it)[0], Map::EMPTY);
	while (it != _position.begin())
	{
		prev = it;
		--prev;
		(*it)[0] = (*prev)[0];
		(*it)[1] = (*prev)[1];
		_map->setTypeAtPos((*it)[1], (*it)[0], Map::PLAYER);
		--it;
	}
	(*it)[0] = _next[0];
	(*it)[1] = _next[1];
	int type = _map->getTypeAtPos((int)(*it)[1], (int)(*it)[0]);
	_map->setTypeAtPos((*it)[1], (*it)[0], Map::PLAYER);
	if (type == Map::POWERUP)
	{
		if (grow() == false)
			return false;
		_map->genPowerUp(*this);
	}
	return genNext();
}

bool Character::genNext()
{
	if (_direction == UP)
	{
		if (_position[0][0] == 0)
			return false;
		_next[0] = _position[0][0] - 1;
		_next[1] = _position[0][1];
	}
	else if (_direction == DOWN)
	{
		if (_position[0][0] == 0)
			return false;
		_next[0] = _position[0][0] + 1;
		_next[1] = _position[0][1];
	}
	else if (_direction == LEFT)
	{
		if (_position[0][1] == 0)
			return false;
		_next[0] = _position[0][0];
		_next[1] = _position[0][1] - 1;
	}
	else if (_direction == RIGHT)
	{
		if (_position[0][1] == 0)
			return false;
		_next[0] = _position[0][0];
		_next[1] = _position[0][1] + 1;
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
	if (checkOK() == false)
		return false;
	return makeMove();
}

bool Character::moveUp()
{
	if (_direction == DOWN || _direction == UP)
		return true;
	_direction = UP;
	_next[0] = _position[0][0] - 1;
	_next[1] = _position[0][1];
	return checkOK();
}

bool Character::moveDown()
{
	if (_direction == DOWN || _direction == UP)
		return true;
	_direction = DOWN;
	_next[0] = _position[0][0] + 1;
	_next[1] = _position[0][1];
	return checkOK();
}

bool Character::moveLeft()
{
	if (_direction == RIGHT || _direction == LEFT)
		return true;
	_direction = LEFT;
	_next[0] = _position[0][0];
	_next[1] = _position[0][1] - 1;
	return checkOK();
}

bool Character::moveRight()
{
	if (_direction == RIGHT || _direction == LEFT)
		return true;
	_direction = RIGHT;
	_next[0] = _position[0][0];
	_next[1] = _position[0][1] + 1;
	return checkOK();
}

bool Character::checkOK()
{
		if (_map->getTypeAtPos(_next[1], _next[0]) == Map::BLOCK || _map->getTypeAtPos(_next[1], _next[0]) == Map::ERROR)
		return false;
	for (std::vector<int *>::iterator it = _position.begin(); it != _position.end(); ++it)
	{
		if (_next[0] == (*it)[0] && _next[1] == (*it)[1])
			return false;
	}
	return true;
}

std::vector<int *>Character::getPosition()
{
	return (_position);
}
