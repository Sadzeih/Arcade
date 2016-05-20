//
// SDLLib.hpp for SDLLib.hpp in /home/thomas/rendu/tek2/C++/cpp_arcade/lib/SDL/include
//
// Made by raout_t
// Login   <thomas@epitech.net>
//
// Started on  Fri Mar 11 13:40:25 2016 raout_t
// Last update Fri Apr  1 14:44:43 2016 Alexis Guerville
//

#ifndef		_SDLLIB_HPP_
# define	_SDLLIB_HPP_

#include	<map>
#include	"IGfx.hpp"
#include	"SDL/SDL.h"
#include	"SDL_Image/SDL_image.h"

#define		UTR	0
#define		ROL 	1
#define		RTD 	2
#define		HU 	3
#define		HR 	4
#define		DTR 	5
#define		DOU 	6
#define		HL 	7
#define		HD 	8
#define		RTL 	9
#define		TU 	10
#define		TR 	11
#define		APPLE 	12
#define		TL 	13
#define		TD 	14

class SDLLib : public IGfx
{
private:
  int winWidth;
  int winHeight;
  SDL_Rect rect;
  SDL_Rect clip[15];

  SDL_Window *win;

  SDL_Renderer *pRender;

  SDL_Surface *bgImg;
  SDL_Surface *pastilleImg;
  SDL_Surface *shroomImg;
  SDL_Surface *wallImg;
  SDL_Surface *snakeImg;
  SDL_Surface *devosImg;
  SDL_Surface *snakeLogoImg;
  SDL_Surface *pacmanLogoImg;
  SDL_Surface *beerImg;
  SDL_Surface *pacmanUpImg;
  SDL_Surface *pacmanDownImg;
  SDL_Surface *pacmanLeftImg;
  SDL_Surface *pacmanRightImg;
  SDL_Surface *ghostImg;

  SDL_Texture *shroomTexture;
  SDL_Texture *bgTexture;
  SDL_Texture *pastilleTexture;
  SDL_Texture *wallTexture;
  SDL_Texture *snakeTexture;
  SDL_Texture *devosTexture;
  SDL_Texture *pacmanLogoTexture;
  SDL_Texture *snakeLogoTexture;
  SDL_Texture *beerTexture;
  SDL_Texture *pacmanUpTexture;
  SDL_Texture *pacmanLeftTexture;
  SDL_Texture *pacmanRightTexture;
  SDL_Texture *pacmanDownTexture;
  SDL_Texture *ghostTexture;

	void clear();
  public:
  SDLLib(int width, int height);
  ~SDLLib();

  void setRect(SDL_Rect *rect, int w, int h, int x, int y);
  void display(struct timeval &);
  void drawPastille(int width, int height, int x, int y);
  void drawCase(int width, int height, int x, int y);
  void drawWall(int width, int height, int, int);
  void drawItem(int width, int height, int, int);
  void drawCharacter(int, int, int, int, std::string const);
  void drawPacman(int, int, int, int, int);
  void menuUp();
  void menuDown();
  void initClip();
  int getEvent();
	double getTimeDiff(struct timeval pTime) const;
	void getTime(struct timeval *pTime) const;
  int menu();
};

#endif		/* _SDLLLIB_HPP_ */
