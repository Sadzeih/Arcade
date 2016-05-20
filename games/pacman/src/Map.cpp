//
// Map.cpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/games/pacman/src/
//
// Made by François Devos
// Login   <devos_f@epitech.eu>
//
// Started on  Wed Mar 30 18:01:49 2016 François Devos
// Last update Sat Apr  2 20:27:08 2016 Alexis Guerville
//

#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
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
	std::string line;
	std::ifstream confFile ("pacman-map.txt");

	i = 0;
	j = 0;
	if (confFile.is_open())
	{
		while (i < _width)
		{
			getline(confFile, line);
			for ( std::string::iterator it=line.begin(); it!=line.end(); ++it)
			{
				if (*it == 'B')
				{
					_map[i][j] = BLOCK;
				} else if (*it == ' ') {
					_map[i][j] = PASTILLE;
				} else if (*it == 'P') {
					_map[i][j] = POWERUP;
				} else if (*it == '.') {
					_map[i][j] = INTERSECTION;
				} else if (*it == 'E') {
					_map[i][j] = EVIL_DUDE;
				}
				j++;
			}
			j = 0;
			i++;
		}
	} else {
		std::cerr << "Couldn't open pacman-map.txt file" << std::endl;
		exit(EXIT_FAILURE);
	}
	confFile.close();
}

Map::Type Map::getTypeAtPos(int width, int height) const
{
	if (height >= _height || height < 0)
		return (Map::Type::ERROR);
		// throw Exception("Height provided is outside of map.");
	if (width >= _width || width < 0)
		return (Map::Type::ERROR);
		// throw Exception("Width provided is outside of map.");
	return _map[height][width];
}

void Map::setTypeAtPos(int width, int height, Type type)
{
	if (height >= _height || height < 0)
		return;
		// throw Exception("Height provided is outside of map.");
	if (width >= _width || width < 0)
		return;
		// throw Exception("Width provided is outside of map.");
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
