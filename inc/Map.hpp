//
// Map.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/games/snake/include/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 17:01:58 2016 Alexis Guerville
// Last update Tue Mar 29 15:54:25 2016 Thomas Raout
//

#ifndef MAP_HPP_
#define MAP_HPP_

class Character;

class Map
{
public:
	enum Type
  {
    EMPTY = 0,
    BLOCK = 1,
	PLAYER = 2,
    EVIL_DUDE = 3, //
    PASTILLE = 4,
    POWERUP = 6,
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
	void draw();

	int const &getTypeAtPos(int width, int height) const;
	void setTypeAtPos(int width, int height, Type type);

	int getHeight() const;
	int getWidth() const;

private:
	int _width;
	int _height;
	int **_map;
};

#endif
