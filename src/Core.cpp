//
// Core.cpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/src/
//
// Made by François Devos
// Login   <devos_f@epitech.eu>
//
// Started on  Thu Mar 10 12:57:50 2016 François Devos
// Last update Sat Apr  2 18:23:08 2016 François Devos
//

#include <ctime>
#include <sys/time.h>
#include <cerrno>
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include "Core.hpp"
#include "Exception.hpp"
#include "DLLoader.hpp"

Core::Core(std::string const& default_gfx)
{
	std::map<std::string, std::string>::iterator it;
	int i = 0;
	bool exist = false;

	this->_gfx_path["opengl"] = "./lib/lib_arcade_opengl.so";
	this->_gfx_path["sdl"] = "./lib/lib_arcade_sdl.so";
	this->_gfx_path["libcaca"] = "./lib/lib_arcade_libcaca.so";
	this->_games_path["snake"] = "./games/lib_arcade_snake.so";
	this->_games_path["pacman"] = "./games/lib_arcade_pacman.so";
	for (it = this->_gfx_path.begin(); it != this->_gfx_path.end(); it++){
		if (it->second == default_gfx){
			this->_gfx_position = i;
			exist = true;
		}
		i++;
	}
	if (exist == false)
		throw Exception("Bad gfx library.");
	this->_games_position = 0;
	this->_current_gfx = NULL;
	this->_current_game = NULL;
	_map = NULL;

}

Core::~Core()
{

}

Core::Core(Core const & other)
{
	this->_gfx_path = other._gfx_path;
	this->_games_path = other._games_path;
	this->_games_position = other._games_position;
	this->_gfx_position = other._gfx_position;
	this->_current_gfx = other._current_gfx;
	this->_current_game = other._current_game;
	this->_map = other._map;
}

Core& Core::operator=(Core const &other)
{
	this->_gfx_path = other._gfx_path;
	this->_games_path = other._games_path;
	this->_games_position = other._games_position;
	this->_gfx_position = other._gfx_position;
	this->_current_gfx = other._current_gfx;
	this->_current_game = other._current_game;
	this->_map = other._map;
	return (*this);
}

void Core::menu()
{
	if (_current_gfx->menu() == 1)
		this->_games_position = 1;
	else
		this->_games_position = 0;
	if (_current_game != NULL)
		delete _current_game;
	DLLoader<IGame> *gameLoader = new DLLoader<IGame>(getGameFromPos());
	_current_game = gameLoader->getInstance("createGame", 40, 40);
	if (_current_game == NULL)
		throw Exception("Game lib not found.");
	launch();
}

void Core::restart()
{
	if (_current_game != NULL)
		delete _current_game;
	DLLoader<IGame> *gameLoader = new DLLoader<IGame>(getGameFromPos());
	_current_game = gameLoader->getInstance("createGame", 40, 40);
	if (_current_game == NULL)
		throw Exception("Game lib not found.");
	launch();
}

void Core::load()
{
	DLLoader<IGfx> *gfxLoader = new DLLoader<IGfx>(getGfxFromPos());

	_current_gfx = gfxLoader->getInstance("createLib");
	if (_current_gfx == NULL)
		throw Exception("Graphics lib not found.");

	menu();
	return;
}

void Core::getTime(struct timeval *pTime) const
{
	if (gettimeofday(pTime, NULL) == -1)
		throw Exception(std::strerror(errno));
}

void Core::launch()
{
	struct timeval pTime;
	struct timeval dTime;
	bool live = true;
	int tmpEvent;
	int event;

	getTime(&pTime);
	getTime(&dTime);
	std::srand(std::time(0));
	_current_game->generateMap();
	_map = _current_game->getMap();
	event = 0;
	while (live)
	{
		_current_gfx->clear();
		drawMap();
		_current_gfx->display(dTime);
		tmpEvent = _current_gfx->getEvent();
		if (tmpEvent == QUIT)
			return;
		if (tmpEvent != NOTHING)
			event = tmpEvent;
		events(event);
		live = _current_game->update(pTime, event);
	}
	menu();
}

void Core::events(int &event)
{
	if (event == NEXT_GAME)
		nextGame();
	else if (event == PREV_GAME)
		prevGame();
	else if (event == NEXT_LIB)
		nextGfx();
	else if (event == PREV_LIB)
		prevGfx();
	else if (event == RESTART)
		restart();
	else if (event == MENU)
		menu();
	if (event == NEXT_GAME || event == PREV_GAME || event == NEXT_LIB ||\
	event == PREV_LIB || event == RESTART || event == MENU)
		event = NOTHING;
}


void Core::drawMap()
{
	int todraw;

	for (int height = 0; height < _map->getHeight(); height++)
	{
		for (int width = 0; width < _map->getWidth(); width++)
		{
			todraw = _map->getTypeAtPos(width, height);
			if (todraw == Map::EMPTY)
				_current_gfx->drawCase(width, height, _map->getWidth(), _map->getHeight());
			else if (todraw == Map::POWERUP)
				_current_gfx->drawItem(width, height, _map->getWidth(), _map->getHeight());
			else if (todraw == Map::BLOCK)
				_current_gfx->drawWall(width, height, _map->getWidth(), _map->getHeight());
			else if (todraw == Map::PLAYER)
				_current_gfx->drawCharacter(width, height, _map->getWidth(), _map->getHeight(), "snake");
			else if (todraw == Map::PACMAN_UP)
				_current_gfx->drawCharacter(width, height, _map->getWidth(), _map->getHeight(), "pacman-up");
			else if (todraw == Map::PACMAN_DOWN)
				_current_gfx->drawCharacter(width, height, _map->getWidth(), _map->getHeight(), "pacman-down");
			else if (todraw == Map::PACMAN_RIGHT)
				_current_gfx->drawCharacter(width, height, _map->getWidth(), _map->getHeight(), "pacman-right");
			else if (todraw == Map::PACMAN_LEFT)
				_current_gfx->drawCharacter(width, height, _map->getWidth(), _map->getHeight(), "pacman-left");
			else if (todraw == Map::EVIL_DUDE)
				_current_gfx->drawCharacter(width, height, _map->getWidth(), _map->getHeight(), "ghost");
			else if (todraw == Map::PASTILLE)
				_current_gfx->drawPastille(width, height, _map->getWidth(), _map->getHeight());
//			else if (todraw == Map::PACMAN)
//				_current_gfx->drawPacman(width, height, _map->getWidth(), _map->getHeight(), _current_game->getCharacter()->getDirection());
		}
	}
}

int Core::getGamesPos()
{
	return (this->_games_position);
}

int Core::getGfxPos()
{
	return (this->_gfx_position);
}

std::string const& Core::getGfxFromPos()
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	for (it = this->_gfx_path.begin(); it != this->_gfx_path.end() && i != _gfx_position; it++){
		i++;
	}
	return it->second;
}

std::string const& Core::getGameFromPos()
{
	int i = 0;
	std::map<std::string, std::string>::iterator it;

	for (it = this->_games_path.begin(); it != this->_games_path.end() && i != _games_position; it++){
		i++;
	}
	return it->second;
}

void Core::nextGame()
{
	int posMax = _games_path.size() - 1;

	_games_position++;
	if (_games_position > posMax)
		_games_position = 0;
	if (_current_game != NULL)
		delete _current_game;
	DLLoader<IGame> *gameLoader = new DLLoader<IGame>(getGameFromPos());
	_current_game = gameLoader->getInstance("createGame", 40, 40);
	_current_game->generateMap();
	_map = _current_game->getMap();
}

void Core::prevGame()
{
	int posMax = _games_path.size() - 1;

	if (_games_position == 0)
		_games_position = posMax;
	else
		_games_position--;
	delete _current_game;
	DLLoader<IGame> *gameLoader = new DLLoader<IGame>(getGameFromPos());
	_current_game = gameLoader->getInstance("createGame", 40, 40);
	_current_game->generateMap();
	_map = _current_game->getMap();
}

void Core::nextGfx()
{
	int posMax = _gfx_path.size() - 1;

	_gfx_position++;
	if (_gfx_position > posMax)
		_gfx_position = 0;
	delete _current_gfx;
	DLLoader<IGfx> *gfxLoader = new DLLoader<IGfx>(getGfxFromPos());
	_current_gfx = gfxLoader->getInstance("createLib");
}

void Core::prevGfx()
{
	int posMax = _gfx_path.size() - 1;

	if (_gfx_position == 0)
		_gfx_position = posMax;
	else
		_gfx_position--;
	delete _current_gfx;
	DLLoader<IGfx> *gfxLoader = new DLLoader<IGfx>(getGfxFromPos());
	_current_gfx = gfxLoader->getInstance("createLib");
}
