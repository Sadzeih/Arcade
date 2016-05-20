//
// Map.hpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/games/pacman/include/
//
// Made by François Devos
// Login   <devos_f@epitech.eu>
//
// Started on  Wed Mar 30 18:00:02 2016 François Devos
// Last update Sat Apr  2 13:56:19 2016 François Devos
//

#ifndef MAP_HPP_
#define MAP_HPP_

class Character;

class Map
{
public:
	enum Type
	{
		ERROR = -1,
		EMPTY = 0,
		BLOCK = 1,
		PLAYER = 2,
    EVIL_DUDE = 3, //fantomes
    PASTILLE = 4,
    INTERSECTION = 5,
    POWERUP = 6, //pour manger les enemies
    PACMAN_UP = 7,
    PACMAN_DOWN = 8,
    PACMAN_LEFT = 9,
    PACMAN_RIGHT = 10
};

Map(int width, int height);
~Map();

Map(Map const&);
Map &operator=(Map const&);

void generate();

Type getTypeAtPos(int width, int height) const;
void setTypeAtPos(int width, int height, Type type);

int **getMap() const;
int getHeight() const;
int getWidth() const;

private:
	int _width;
	int _height;
	Type **_map;
};

#endif
