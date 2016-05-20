//
// Pacman.cpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/games/pacman/src/
//
// Made by François Devos
// Login   <devos_f@epitech.eu>
//
// Started on  Wed Mar 30 18:35:17 2016 François Devos
// Last update Sun Apr  3 15:56:59 2016 Alexis Guerville
//

#include <vector>
#include <iostream>
#include <sys/time.h>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "Pacman.hpp"
#include "Map.hpp"
#include "IGfx.hpp"
#include "Protocol.hpp"
#include "Ghost.hpp"
#include "Exception.hpp"

Pacman::Pacman(int width, int height)
{
	_map = new Map(width, height);
	_character = new Character(_map);
	initGhosts();
}

Pacman::~Pacman()
{
	delete _map;
}

Map *Pacman::getMap() const
{
	return _map;
}

void Pacman::initGhosts()
{
	_ghosts.push_back(new Ghost(_map, 2, 1));
	_ghosts.push_back(new Ghost(_map, 36, 1));
	_ghosts.push_back(new Ghost(_map, 2, 38));
	_ghosts.push_back(new Ghost(_map, 36, 38));
}

void Pacman::generateMap() const
{

}

double Pacman::getTimeDiff(struct timeval pTime) const
{
	double timeDiff;
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		throw Exception(std::strerror(errno));
	timeDiff = (tv.tv_sec - pTime.tv_sec) * 1000.0;
	timeDiff += (tv.tv_usec - pTime.tv_usec) / 1000.0;
	return timeDiff;
}

void Pacman::getTime(struct timeval *pTime) const
{
	if (gettimeofday(pTime, NULL) == -1)
		throw Exception(std::strerror(errno));
}

bool Pacman::update(struct timeval &pTime, int &direction)
{
	int *ghostNext;
	int *charNext;
	int *ghostPos;
	static struct timeval startTime = pTime;
	std::vector<Ghost *>::iterator it;
	bool live = true;

	if (getTimeDiff(pTime) >= 150)
	{
		getTime(&pTime);
		for (it = _ghosts.begin(); it != _ghosts.end(); ++it)
		{
			ghostPos = (*it)->getPosition();
			ghostNext = (*it)->getNext();
			charNext = _character->getNext();
			if (ghostNext[0] == charNext[0] && ghostNext[1] == charNext[1])
			{
				if (_character->getWeak() == 1)
					return false;
				else
				{
					_map->setTypeAtPos(ghostNext[1], ghostNext[0], Map::EMPTY);
					it = _ghosts.erase(it);
				}
			}
			else if (charNext[0] == ghostPos[0] && charNext[1] == ghostNext[1] && _character->getWeak() == 0)
			{
				_map->setTypeAtPos(ghostNext[1], ghostNext[0], Map::EMPTY);
				it = _ghosts.erase(it);
			}
		}
		live = _character->move(static_cast<Character::Direction>(direction));
		direction = 0;
		for (it = _ghosts.begin(); it != _ghosts.end(); ++it)
			(*it)->move();

		if (getTimeDiff(startTime) >= 10000)
		{
			_character->weaken();
			getTime(&startTime);
		}
	}
	return live;
}

Character *Pacman::getCharacter() const
{
	return (this->_character);
}

static void getWhereAmI(arcade::CommandType cmd, Pacman *player)
{
	arcade::WhereAmI *me;
	me = reinterpret_cast<struct arcade::WhereAmI *>(new char[sizeof(struct arcade::WhereAmI) + (sizeof(struct arcade::Position))]);
	int i;

	me->type = cmd;
	me->lenght = 1;
	i = 0;
	for (int y = 0; y < player->getMap()->getHeight(); y++){
		for (int x = 0; x < player->getMap()->getWidth(); x++){
			if (player->getMap()->getTypeAtPos(x, y) == Map::Type::PLAYER)
			{
				me->position[i].x = x;
				me->position[i].y = y;
				i++;
			}
		}
	}
	write(1, me, sizeof(struct arcade::WhereAmI) + (sizeof(struct arcade::Position)));
	//delete me;
}

static void getGetMap(arcade::CommandType cmd, Pacman *player)
{
	arcade::GetMap *map;
	map = reinterpret_cast<struct arcade::GetMap*>(new uint16_t[sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * (player->getMap()->getWidth() * player->getMap()->getHeight())]);

	map->type = cmd;
	map->width = player->getMap()->getWidth();
	map->height = player->getMap()->getHeight();

	for (int y = 0; y < player->getMap()->getHeight(); y++){
		for (int x = 0; x < player->getMap()->getWidth(); x++){
			if (player->getMap()->getTypeAtPos(x, y) == Map::Type::EMPTY)
				map->tile[y * player->getMap()->getHeight() + x] = arcade::TileType::EMPTY;
			else if (player->getMap()->getTypeAtPos(x, y) == Map::Type::BLOCK)
				map->tile[y * player->getMap()->getHeight() + x] = arcade::TileType::BLOCK;
			else
				map->tile[y * player->getMap()->getHeight() + x] = arcade::TileType::EMPTY;
		}
	}
	write(1, map, sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * (player->getMap()->getWidth() * player->getMap()->getHeight()));

}

extern "C"
{
	void Play()
	{
		arcade::CommandType cmd; //sert a recuperer la commande
		Character::Direction dir;
		Pacman *player;
		player = new Pacman(40, 40);
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
		return new Pacman(width, height);
	}
}
