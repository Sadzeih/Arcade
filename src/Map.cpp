//
// Map.cpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/games/snake/src/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 17:34:35 2016 Alexis Guerville
// Last update Tue Mar 29 15:45:47 2016 Thomas Raout
//

#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include "Map.hpp"
#include "Exception.hpp"

Map::Map(int width, int height)
: _width(width), _height(height)
{
  _map = new int*[_height];
  for (int i = 0; i < _height; i++)
    {
      _map[i] = new int[_width];
    }
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
  _map = new int*[copy._height];
  for (int i = 0; i < copy._height; i++)
    {
      _map[i] = new int[copy._width];
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
      _map = new int*[copy._height];
      for (int i = 0; i < copy._height; i++)
	{
	  _map[i] = new int[copy._width];
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

int const &Map::getTypeAtPos(int width, int height) const
{
  if (height >= _height || height < 0)
    throw Exception("Height provided is outside of map.");
  if (width >= _width || width < 0)
    throw Exception("Width provided is outside of map.");
  return _map[height][width];
}

void Map::setTypeAtPos(int width, int height, Type type)
{
  if (height >= _height || height < 0)
    throw Exception("Height provided is outside of map.");
  if (width >= _width || width < 0)
    throw Exception("Width provided is outside of map.");
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
