//
// cacaLib.hpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/lib/libcaca/include
//
// Made by François Devos
// Login   <devos-f@epitech.net>
//
// Started on  Fri Mar 11 11:32:52 2016 François Devos
// Last update Fri Apr  1 10:51:48 2016 Alexis Guerville
//

#ifndef CACALIB_HPP_
#define CACALIB_HPP_

#include <ctime>
#include "caca/caca.h"
#include "IGfx.hpp"

class cacaLib: public IGfx
{
  caca_canvas_t *cv;
  caca_display_t *dp;
  caca_event_t	ev;
  int         width;
  int         height;

  void clear();
public:
  cacaLib(int width, int height);
  ~cacaLib();

  void display(struct timeval&);
	void drawCase(int width, int height, int, int);
	void drawWall(int width, int height, int, int);
  void drawPastille(int width, int height, int, int);
	void drawItem(int width, int height, int, int);
  void drawCharacter(int, int, int, int, std::string const);
  void drawPacman(int, int, int, int, int);
  int getEvent();
	int menu();
	double getTimeDiff(struct timeval pTime) const;
	void getTime(struct timeval *pTime) const;
};

#endif
