//
// Map.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/games/snake/include/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 17:01:58 2016 Alexis Guerville
// Last update Sat Apr  2 17:08:23 2016 Alexis Guerville
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
    POWERUP = 6
  };

	Map(int width, int height);
	~Map();

	Map(Map const&);
	Map &operator=(Map const&);

	void generate();

	Type getTypeAtPos(int width, int height) const;
	void setTypeAtPos(int width, int height, Type type);
	void genPowerUp(Character &);

	int **getMap() const;
	int getHeight() const;
	int getWidth() const;

private:
	int _width;
	int _height;
	Type **_map;
};

#endif
