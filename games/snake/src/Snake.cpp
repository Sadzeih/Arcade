//
// Snake.cpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/games/snake/src/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 17:22:36 2016 Alexis Guerville
// Last update Sat Apr  2 15:45:29 2016 François Devos
//

#include <vector>
#include <iostream>
#include <sys/time.h>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "Snake.hpp"
#include "Map.hpp"
#include "IGfx.hpp"
#include "Protocol.hpp"
#include "Exception.hpp"

Snake::Snake(int width, int height)
{
	_map = new Map(width, height);
	_character = new Character(_map);
}

Snake::~Snake()
{
	delete _map;
}

Map *Snake::getMap() const
{
	return _map;
}

void Snake::generateMap() const
{
	this->_map->genPowerUp(*_character);
}

double Snake::getTimeDiff(struct timeval pTime) const
{
	double timeDiff;
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		throw Exception(std::strerror(errno));
	timeDiff = (tv.tv_sec - pTime.tv_sec) * 1000.0;
  timeDiff += (tv.tv_usec - pTime.tv_usec) / 1000.0;
	return timeDiff;
}

void Snake::getTime(struct timeval *pTime) const
{
	if (gettimeofday(pTime, NULL) == -1)
		throw Exception(std::strerror(errno));
}

bool Snake::update(struct timeval &pTime, int &direction)
{
	bool live = true;

	if (getTimeDiff(pTime) >= 100)
	{
	 	getTime(&pTime);
		live = _character->checkOK();
		live = _character->move(static_cast<Character::Direction>(direction));
		direction = 0;
	}
	return live;
}

Character *Snake::getCharacter() const
{
	return (this->_character);
}

static void getWhereAmI(arcade::CommandType cmd, Snake *player)
{
	arcade::WhereAmI *me;
	me = reinterpret_cast<struct arcade::WhereAmI *>(new char[sizeof(struct arcade::WhereAmI) + (sizeof(struct arcade::Position) * player->getCharacter()->getPosition().size())]);
	std::vector<int *>::iterator it;
	int i;

	i = 0;
	me->type = cmd;
	me->lenght = player->getCharacter()->getPosition().size();
	std::cerr << player->getCharacter()->getPosition()[0][0] << std::endl;
	it = player->getCharacter()->getPosition().begin();
	while (i < me->lenght)
	{
		me->position[i].x = player->getCharacter()->getPosition()[i][1];
		me->position[i].y = player->getCharacter()->getPosition()[i][0];
		i++;
	}
	write(1, me, sizeof(struct arcade::WhereAmI) + (sizeof(struct arcade::Position) * player->getCharacter()->getPosition().size()));
	//delete me;
}

static void getGetMap(arcade::CommandType cmd, Snake *player)
{
	arcade::GetMap *map;
	map = reinterpret_cast<struct arcade::GetMap*>(new char[sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * (player->getMap()->getWidth() * player->getMap()->getHeight())]);

	map->type = cmd;
	map->width = player->getMap()->getWidth();
	map->height = player->getMap()->getHeight();

	for (int y = 0; y < player->getMap()->getHeight(); y++){
		for (int x = 0; x < player->getMap()->getWidth(); x++){
			if (player->getMap()->getTypeAtPos(x, y) == Map::Type::EMPTY)
				map->tile[y * player->getMap()->getHeight() + x] = arcade::TileType::EMPTY;
			else if (player->getMap()->getTypeAtPos(x, y) == Map::Type::BLOCK)
				map->tile[y * player->getMap()->getHeight() + x] = arcade::TileType::BLOCK;
			else if (player->getMap()->getTypeAtPos(x, y) == Map::Type::PLAYER)
				map->tile[y * player->getMap()->getHeight() + x] = arcade::TileType::EMPTY; // a voir
			else if (player->getMap()->getTypeAtPos(x, y) == Map::Type::POWERUP)
				map->tile[y * player->getMap()->getHeight() + x] = arcade::TileType::POWERUP;
		}
	}
	write(1, map, sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * (player->getMap()->getWidth() * player->getMap()->getHeight()));
	//delete map;
}

extern "C"
{
	void Play()
	{
		arcade::CommandType cmd; //sert a recuperer la commande
		Character::Direction dir;
		Snake *player;
		player = new Snake(20, 20);
		dir = Character::Direction::FORWARD;
		while (read(0, &cmd, sizeof(arcade::CommandType)))
		{
			if (cmd == arcade::CommandType::GET_MAP)
			{
				dir = Character::Direction::FORWARD;
				getGetMap(cmd, player);
			}
			else if (cmd == arcade::CommandType::WHERE_AM_I)
			{
				dir = Character::Direction::FORWARD;
				getWhereAmI(cmd, player);
			}
			else if (cmd == arcade::CommandType::GO_UP)
				dir = Character::Direction::UP;
			else if (cmd == arcade::CommandType::GO_DOWN)
				dir = Character::Direction::DOWN;
			else if (cmd == arcade::CommandType::GO_LEFT)
				dir = Character::Direction::LEFT;
			else if (cmd == arcade::CommandType::GO_RIGHT)
				dir = Character::Direction::RIGHT;
			else if (cmd == arcade::CommandType::GO_FORWARD)
				dir = Character::Direction::FORWARD;
			else if (cmd == arcade::CommandType::PLAY)
				player->getCharacter()->move(dir);
		}
	}
}

extern "C"
{
	IGame *createGame(int width, int height)
	{
		return new Snake(width, height);
	}
}
