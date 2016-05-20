//
// cacaLib.cpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/lib/libcaca
//
// Made by François Devos
// Login   <devos-f@epitech.net>
//
// Started on  Fri Mar 11 11:39:09 2016 François Devos
// Last update Sun Apr  3 16:18:03 2016 François Devos
//

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sys/time.h>
#include "caca/caca.h"
#include "cacaLib.hpp"
#include "Exception.hpp"

cacaLib::cacaLib(int width, int height)
{
  this->cv = caca_create_canvas(width, height);
  this->dp = caca_create_display(this->cv);
  caca_set_display_time(this->dp, 20);
  if (!this->dp)
    exit(-1);
  this->width = width;
  this->height = height;
}

cacaLib::~cacaLib()
{
  caca_free_display(this->dp);
}

void cacaLib::clear()
{
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLACK);
  caca_clear_canvas(this->cv);
}

void cacaLib::drawCase(int width, int height, int mapWidth, int mapHeight)
{
  (void)mapWidth;
  (void)mapHeight;
  (void)width;
  (void)height;
}

void cacaLib::drawWall(int width, int height, int mapWidth, int mapHeight)
{
  (void)mapWidth;
  (void)mapHeight;
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLUE);
  caca_put_char(this->cv, width, height, 0023);
}

void cacaLib::drawPastille(int width, int height, int mapWidth, int mapHeight)
{
  (void)mapWidth;
  (void)mapHeight;

  caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
  caca_put_char(this->cv, width, height, 0056);
}

void cacaLib::drawItem(int width, int height, int mapWidth, int mapHeight)
{
  (void)mapWidth;
  (void)mapHeight;
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_LIGHTRED);
  caca_put_char(this->cv, width, height, 0023);
}

void cacaLib::drawPacman(int width, int height, int mapWidth, int mapHeight, int direction)
{
  (void)width;
  (void)height;
  (void)mapWidth;
  (void)mapHeight;
  (void)direction;
}

void cacaLib::drawCharacter(int width, int height, int mapWidth, int mapHeight, std::string const spriteName)
{
  (void)mapWidth;
  (void)mapHeight;
  if (spriteName == "snake")
  {
    caca_set_color_ansi(this->cv, CACA_BLACK, CACA_GREEN);
    caca_put_char(this->cv, width, height, 0023);
  }
  else if (spriteName.find("pacman") != std::string::npos)
  {
    caca_set_color_ansi(this->cv, CACA_BLACK, CACA_YELLOW);
    caca_put_char(this->cv, width, height, 0023);
  }
  else if (spriteName == "ghost")
  {
    caca_set_color_ansi(this->cv, CACA_BLACK, CACA_RED);
    caca_put_char(this->cv, width, height, 0023);
  }
  //caca_refresh_display(this->dp);
}

int cacaLib::getEvent()
{
  caca_get_event(this->dp, CACA_EVENT_KEY_PRESS, &this->ev,100000);
  if (caca_get_event_type(&this->ev) == CACA_EVENT_KEY_PRESS){
    if (caca_get_event_key_ch(&this->ev) == CACA_KEY_LEFT)
      return (IGfx::LEFT);
    else if (caca_get_event_key_ch(&this->ev) == CACA_KEY_RIGHT)
      return (IGfx::RIGHT);
    else if (caca_get_event_key_ch(&this->ev) == CACA_KEY_UP)
      return (IGfx::UP);
    else if (caca_get_event_key_ch(&this->ev) == CACA_KEY_DOWN)
      return (IGfx::DOWN);
    else if (caca_get_event_key_ch(&this->ev) == 38)
      return (IGfx::NEXT_GAME);
    else if (caca_get_event_key_ch(&this->ev) == 233)
      return (IGfx::PREV_GAME);
    else if (caca_get_event_key_ch(&this->ev) == 34)
    {
      caca_free_canvas(this->cv);
      return (IGfx::NEXT_LIB);
    }
    else if (caca_get_event_key_ch(&this->ev) == 39)
    {
      caca_free_canvas(this->cv);
      return (IGfx::PREV_LIB);
    }
    else if (caca_get_event_key_ch(&this->ev) == 40)
      return (IGfx::RESTART);
    else if (caca_get_event_key_ch(&this->ev) == CACA_KEY_ESCAPE)
    {
      caca_free_canvas(this->cv);
      return (IGfx::QUIT);
    }
  }
  return (0);
}

int cacaLib::menu()
{
  int choose;

  choose = 1; //Snake

  caca_clear_canvas(this->cv);
  caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
  caca_put_str(this->cv, 20, 5, "WELCOME TO CACARCADE !");
  caca_put_str(this->cv, 20, 19, "---------");
  caca_put_str(this->cv, 20, 20, "| SNAKE |");
  caca_put_str(this->cv, 20, 21, "---------");
  caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
  caca_put_str(this->cv, 20, 30, "PACMAN");
  caca_refresh_display(this->dp);

  while (42){
    caca_get_event(this->dp, CACA_EVENT_KEY_PRESS, &this->ev,100000);
    if (choose == 1)
    {
      caca_clear_canvas(this->cv);
      caca_put_str(this->cv, 20, 5, "WELCOME TO CACARCADE !");
      caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
      caca_put_str(this->cv, 20, 19, "---------");
      caca_put_str(this->cv, 20, 20, "| SNAKE |");
      caca_put_str(this->cv, 20, 21, "---------");
      caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
      caca_put_str(this->cv, 20, 30, "PACMAN");
    }
    else if (choose == 0)
    {
      caca_clear_canvas(this->cv);
      caca_put_str(this->cv, 20, 5, "WELCOME TO CACARCADE !");
      caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
      caca_put_str(this->cv, 20, 20, "SNAKE");
      caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
      caca_put_str(this->cv, 20, 29, "----------");
      caca_put_str(this->cv, 20, 30, "| PACMAN |");
      caca_put_str(this->cv, 20, 31, "----------");
    }
    if (caca_get_event_key_ch(&this->ev) == CACA_KEY_UP)
      choose = 1;
    if (caca_get_event_key_ch(&this->ev) == CACA_KEY_DOWN)
      choose = 0;
    if (caca_get_event_key_ch(&this->ev) == CACA_KEY_ESCAPE)
    {
      caca_free_canvas(this->cv);
      exit(0);
    }
    if (caca_get_event_key_ch(&this->ev) == 13)
      break;
    if (caca_get_event_type(&this->ev) == CACA_EVENT_KEY_PRESS)
    caca_refresh_display(this->dp);
  }
  return (choose);
}
double cacaLib::getTimeDiff(struct timeval pTime) const
{
	double timeDiff;
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		throw Exception(std::strerror(errno));
	timeDiff = (tv.tv_sec - pTime.tv_sec) * 1000.0;
  timeDiff += (tv.tv_usec - pTime.tv_usec) / 1000.0;
	return timeDiff;
}

void cacaLib::getTime(struct timeval *pTime) const
{
	if (gettimeofday(pTime, NULL) == -1)
		throw Exception(std::strerror(errno));
}

void cacaLib::display(struct timeval &pTime)
{
	(void)pTime;
  caca_refresh_display(this->dp);
}

extern "C"
{
  IGfx *createLib()
  {
    return new cacaLib(100, 100);
  }
}
