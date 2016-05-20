//
// Map.cpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/games/snake/src/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 17:34:35 2016 Alexis Guerville
// Last update Sat Apr  2 17:28:06 2016 Alexis Guerville
//

#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include "Map.hpp"
#include "Character.hpp"
#include "Exception.hpp"

Map::Map(int width, int height)
: _width(width), _height(height)
{
	_map = new Type*[_height];
	for (int i = 0; i < _height; i++)
	{
		_map[i] = new Type[_width];
	}
	generate();
}

Map::~Map()
{
	for (int i = 0; i < _height; i++)
	{
		delete _map[i];
	}
	delete _map;
}

Map::Map(Map const &copy)
{
	_height = copy._height;
	_width = copy._width;
	_map = new Type*[copy._height];
	for (int i = 0; i < copy._height; i++)
	{
		_map[i] = new Type[copy._width];
	}
}

Map &Map::operator=(Map const &copy)
{
	if (&copy != this)
	{
		for (int i = 0; i < _height; i++)
		{
			delete _map[i];
		}
		delete _map;
		_height = copy._height;
		_width = copy._width;
		_map = new Type*[copy._height];
		for (int i = 0; i < copy._height; i++)
		{
			_map[i] = new Type[copy._width];
		}
	}
	return *this;
}

void Map::generate()
{
	int i;
	int j;

	for (i = 0; i < _height; i++)
	{
		for (j = 0; j < _width; j++)
		{
			if (j == 0 || i == 0 || i == _height - 1 || j == _width - 1)
				_map[i][j] = BLOCK;
			else
				_map[i][j] = EMPTY;
		}
	}
}

Map::Type Map::getTypeAtPos(int width, int height) const
{
	if (height >= (_height - 1) || height < 0)
		return ERROR;
	if (width >= (_width - 1) || width < 0)
		return ERROR;
	return _map[height][width];
}

void Map::setTypeAtPos(int width, int height, Type type)
{
	if (height >= _height || height < 0)
		return;
	if (width >= _width || width < 0)
		return;
	_map[height][width] = type;
}

int Map::getHeight() const
{
	return _height;
}

int Map::getWidth() const
{
	return _width;
}

void Map::genPowerUp(Character &charact)
{
	int randX;
	int randY;
	std::vector<int *> snake;
	std::vector<int *>::iterator it;
	bool find = false;

	snake = charact.getPosition();
	while (find == false)
	{
		find = true;
		randX = std::rand() % _height;
		randY = std::rand() % _width;
		for (it = snake.begin(); it != snake.end(); it++)
		{
			if ((*it)[0] == randX || (*it)[1] == randY)
				find = false;
		}
		if (_map[randX][randY] != EMPTY)
			find = false;
	}
	setTypeAtPos(randY, randX, POWERUP);
}
