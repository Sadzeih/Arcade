//
// Core.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 11:49:28 2016 Alexis Guerville
// Last update Fri Apr  1 14:27:22 2016 Alexis Guerville
//

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include <map>
#include "IGfx.hpp"
#include "IGame.hpp"
#include "Map.hpp"

class Core
{
	std::map<std::string, std::string> _gfx_path;
	std::map<std::string, std::string> _games_path;

	int _games_position;
	int _gfx_position;
	IGfx *_current_gfx;
	IGame *_current_game;

	Map *_map;

	Core(Core const &);
	Core &operator=(Core const &);
public:
	enum Command
	{
		QUIT = -1,
		NOTHING = 0,
		NEXT_GAME = 1,
		PREV_GAME = 2,
		NEXT_LIB = 3,
		PREV_LIB = 4,
		RESTART = 5,
		MENU = 6,
		UP = 7,
		DOWN = 8,
		LEFT = 9,
		RIGHT = 10
	};

	Core(std::string const &);
	~Core();

	void getTime(struct timeval*) const;

	void restart();
	void menu();
	void load();
	void launch();
	void drawMap();

	void events(int &event);

	int getGamesPos();
	int getGfxPos();

	std::string const& getGfxFromPos();
	std::string const& getGameFromPos();

	void nextGame();
	void prevGame();
	void nextGfx();
	void prevGfx();
};

#endif
