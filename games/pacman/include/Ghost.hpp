//
// Ghost.hpp for Ghost.hpp in /home/thomas/rendu/tek2/C++/cpp_arcade
//
// Made by raout_t
// Login   <thomas@epitech.net>
//
// Started on  Sat Apr  2 15:21:08 2016 raout_t
// Last update Sat Apr  2 23:36:12 2016 Alexis Guerville
//

#ifndef _GHOST_HPP
# define _GHOST_HPP_

#include "Map.hpp"
#include "Character.hpp"

class Ghost : public Character
{
	Map::Type _prev;
public:
	Ghost(Map *map, int x, int y);
	~Ghost();

	bool move();
	bool makeMove();
	bool genNext();
	void getDirs(std::vector<Direction> &dirs);
};

#endif
