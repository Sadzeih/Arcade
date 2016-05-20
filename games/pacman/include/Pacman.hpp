//
// Pacman.hpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/games/pacman/include/
//
// Made by François Devos
// Login   <devos_f@epitech.eu>
//
// Started on  Wed Mar 30 17:56:32 2016 François Devos
// Last update Wed Mar 30 18:48:15 2016 François Devos
//

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <ctime>
#include "IGfx.hpp"
#include "IGame.hpp"
#include "Map.hpp"
#include "Character.hpp"

class Ghost;

class Pacman: public IGame
{
	Map *_map;
	Character *_character;
	std::vector<Ghost *> _ghosts;

public:
	enum event
	{
		LEFT = 1,
		RIGHT = 2
	};

	Pacman(int x, int y);
	~Pacman();

	Character *getCharacter() const;
	Map *getMap() const;
	void generateMap() const;
	void initGhosts();
	void getTime(struct timeval*) const;
	double getTimeDiff(struct timeval) const;
	bool update(struct timeval&, int&);

};

extern "C" void Play(); //fonction moulinette

#endif
