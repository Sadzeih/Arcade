//
// Ghost.cpp for Ghost.cpp in /home/thomas/rendu/tek2/C++/cpp_arcade
//
// Made by raout_t
// Login   <thomas@epitech.net>
//
// Started on  Sat Apr  2 15:29:17 2016 raout_t
// Last update Sun Apr  3 01:07:33 2016 Alexis Guerville
//

#include <iostream>
#include "Map.hpp"
#include "Ghost.hpp"

Ghost::Ghost(Map *map, int x, int y) : Character(map)
{
	_weak = 0;
	_map = map;
	_position = new int[2];
	_position[0] = y;
	_position[1] = x;
	_map->setTypeAtPos(x, y, Map::EVIL_DUDE);
	_next = new int[2];
	_next[0] = _position[0] - 1;
	_next[1] = _position[1];
	_prev = Map::PASTILLE;
	_direction = DOWN;
}

Ghost::~Ghost()
{
}

void Ghost::getDirs(std::vector<Direction> &dirs)
{
	if (_map->getTypeAtPos(_position[1] + 1, _position[0]) == Map::EMPTY ||
		_map->getTypeAtPos(_position[1] + 1, _position[0]) == Map::PASTILLE)
		dirs.push_back(RIGHT);
	if (_map->getTypeAtPos(_position[1], _position[0] + 1) == Map::EMPTY ||
		_map->getTypeAtPos(_position[1], _position[0] + 1) == Map::PASTILLE)
		dirs.push_back(DOWN);
	if (_map->getTypeAtPos(_position[1] - 1, _position[0]) == Map::EMPTY ||
		_map->getTypeAtPos(_position[1] - 1, _position[0]) == Map::PASTILLE)
		dirs.push_back(LEFT);
	if (_map->getTypeAtPos(_position[1], _position[0] - 1) == Map::EMPTY ||
		_map->getTypeAtPos(_position[1], _position[0] - 1) == Map::PASTILLE)
		dirs.push_back(UP);
}


bool Ghost::genNext()
{
	if (_direction == UP)
	{
		if (_position[0] == 0)
			return false;
		_next[0] = _position[0] - 1;
		_next[1] = _position[1];
	}
	else if (_direction == DOWN)
	{
		if (_position[0] == 0)
			return false;
		_next[0] = _position[0] + 1;
		_next[1] = _position[1];
	}
	else if (_direction == LEFT)
	{
		if (_position[1] == 0)
			return false;
		_next[0] = _position[0];
		_next[1] = _position[1] - 1;
	}
	else if (_direction == RIGHT)
	{
		if (_position[1] == 0)
			return false;
		_next[0] = _position[0];
		_next[1] = _position[1] + 1;
	}
	return true;
}


bool Ghost::move()
{
	int i;
	std::vector<Direction> dirs;

	getDirs(dirs);
	if ((dirs.size() > 2) || (_map->getTypeAtPos(_next[1], _next[0]) == Map::BLOCK) ||\
	(_map->getTypeAtPos(_next[1], _next[0])) == Map::EVIL_DUDE)
	{
		if (dirs.size() != 0)
		{
			i = rand() % dirs.size();
			_direction = dirs[i];
		}
		genNext();
	}
	return makeMove();
}

bool Ghost::makeMove()
{
	int *prev = new int[2];

	prev[0] = _position[0];
	prev[1] = _position[1];
	Map::Type type = _map->getTypeAtPos(_next[1], _next[0]);
	if (type == Map::BLOCK || type == Map::EVIL_DUDE)
		return genNext();
	_position[0] = _next[0];
	_position[1] = _next[1];
	if (_prev != Map::ERROR)
	{
		_map->setTypeAtPos(prev[1], prev[0], _prev);
		_prev = type;
	}
	else
		_prev = type;
	_map->setTypeAtPos(_position[1], _position[0], Map::EVIL_DUDE);
	return genNext();
}
