//
// Snake.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/games/snake/include/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 16:58:04 2016 Alexis Guerville
// Last update Sat Apr  2 15:34:16 2016 François Devos
//

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <ctime>
#include "IGfx.hpp"
#include "IGame.hpp"
#include "Map.hpp"
#include "Character.hpp"

class Snake: public IGame
{
	Map *_map;
	Character *_character;
public:

	Snake(int x, int y);
	~Snake();
	Character *getCharacter() const;
	Map *getMap() const;
	void generateMap() const;
	void getTime(struct timeval*) const;
	double getTimeDiff(struct timeval) const;
	bool update(struct timeval&, int&);
};

extern "C" void Play(); //fonction moulinette

#endif
