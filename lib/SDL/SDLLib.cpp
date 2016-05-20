//
// SDLLib.cpp for SDLLib.cpp in /home/thomas/rendu/tek2/C++/cpp_arcade/lib/SDL
//
// Made by raout_t
// Login   <thomas@epitech.net>
//
// Started on  Fri Mar 11 13:59:52 2016 raout_t
// Last update Fri Apr  1 14:45:51 2016 Alexis Guerville
//

#include	<unistd.h>
#include	<iostream>
#include	<cstring>
#include	<cerrno>
#include	<sys/time.h>
#include  "Map.hpp"
#include	"SDLLib.hpp"
#include	"Exception.hpp"

SDLLib::SDLLib(int width, int height)
{
  this->winWidth = width;
  this->winHeight = height;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
  }
  this->win = SDL_CreateWindow("SDL", 300, 300,
    width, height, SDL_WINDOW_SHOWN);
  if (win == NULL)
  {
    std::cerr << "SDL_Create_Window Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
  }

  IMG_Init(IMG_INIT_PNG);
  this->pRender = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED);

  this->shroomImg = IMG_Load("shroom.png");
  this->pastilleImg = IMG_Load("pastille.jpg");
  this->bgImg = IMG_Load("bleu-nuit.jpg");
  this->wallImg = IMG_Load("coble.jpg");
  this->devosImg = IMG_Load("devos.jpg");
  this->pacmanLogoImg = IMG_Load("pacman.png");
  this->snakeLogoImg = IMG_Load("snake.png");
  this->beerImg = IMG_Load("beer-maximator.png");

  this->pacmanUpImg = IMG_Load("pacman-up.png");
  this->pacmanUpTexture = SDL_CreateTextureFromSurface(this->pRender, this->pacmanUpImg);
  this->pacmanDownImg = IMG_Load("pacman-down.png");
  this->pacmanDownTexture = SDL_CreateTextureFromSurface(this->pRender, this->pacmanDownImg);
  this->pacmanLeftImg = IMG_Load("pacman-left.png");
  this->pacmanLeftTexture = SDL_CreateTextureFromSurface(this->pRender, this->pacmanLeftImg);
  this->pacmanRightImg = IMG_Load("pacman-right.png");
  this->pacmanRightTexture = SDL_CreateTextureFromSurface(this->pRender, this->pacmanRightImg);
  this->ghostImg = IMG_Load("ghost.png");
  this->ghostTexture = SDL_CreateTextureFromSurface(this->pRender, this->ghostImg);
  this->snakeImg = IMG_Load("square.png");
  this->snakeTexture = SDL_CreateTextureFromSurface(this->pRender, this->snakeImg);


  this->shroomTexture = SDL_CreateTextureFromSurface(this->pRender, this->shroomImg);
  this->pastilleTexture = SDL_CreateTextureFromSurface(this->pRender, this->pastilleImg);
  this->bgTexture = SDL_CreateTextureFromSurface(this->pRender, this->bgImg);
  this->wallTexture = SDL_CreateTextureFromSurface(this->pRender, this->wallImg);
  this->devosTexture = SDL_CreateTextureFromSurface(this->pRender, this->devosImg);
  this->snakeLogoTexture = SDL_CreateTextureFromSurface(this->pRender, this->snakeLogoImg);
  this->pacmanLogoTexture = SDL_CreateTextureFromSurface(this->pRender, this->pacmanLogoImg);
  this->beerTexture = SDL_CreateTextureFromSurface(this->pRender, this->beerImg);


  initClip();
}

SDLLib::~SDLLib()
{
  SDL_Quit();
}

int SDLLib::getEvent()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if ((event.type == SDL_QUIT) || (event.key.keysym.sym == SDLK_ESCAPE))
     exit(EXIT_SUCCESS);
   if (event.type == SDL_KEYUP)
   {
    if (event.key.keysym.sym == SDLK_LEFT)
      return (IGfx::LEFT);

    if (event.key.keysym.sym == SDLK_RIGHT)
      return (IGfx::RIGHT);

    if (event.key.keysym.sym == SDLK_UP)
      return (IGfx::UP);

    if (event.key.keysym.sym == SDLK_DOWN)
      return (IGfx::DOWN);

    if (event.key.keysym.sym == 233)
      return (IGfx::PREV_GAME);

    if (event.key.keysym.sym == 38)
      return (IGfx::NEXT_GAME);

    if (event.key.keysym.sym == 40)
      return (IGfx::RESTART);

    if (event.key.keysym.sym == '"')
    {
      SDL_DestroyWindow(this->win);
      return (IGfx::NEXT_LIB);
    }
    if (event.key.keysym.sym == '\'')
    {
      SDL_DestroyWindow(this->win);
      return (IGfx::PREV_LIB);
    }
  }
}
return (0);
}


double SDLLib::getTimeDiff(struct timeval pTime) const
{
	double timeDiff;
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		throw Exception(std::strerror(errno));
	timeDiff = (tv.tv_sec - pTime.tv_sec) * 1000.0;
  timeDiff += (tv.tv_usec - pTime.tv_usec) / 1000.0;
  return timeDiff;
}

void SDLLib::getTime(struct timeval *pTime) const
{
	if (gettimeofday(pTime, NULL) == -1)
		throw Exception(std::strerror(errno));
}

void	SDLLib::display(struct timeval &running)
{
  if (getTimeDiff(running) > 100)
    SDL_RenderPresent(pRender);
}

void SDLLib::drawPastille(int x, int y, int width, int height)
{
  setRect(&rect, winWidth / width, winHeight / height, (winWidth / width) * x , (winHeight / height) * y);
  SDL_RenderCopy(pRender, pastilleTexture, NULL, &rect);
}

void SDLLib::drawCase(int x, int y, int width, int height)
{
  setRect(&rect, winWidth / width, winHeight / height, (winWidth / width) * x , (winHeight / height) * y);
  SDL_RenderCopy(pRender, bgTexture, NULL, &rect);
}

void SDLLib::drawWall(int x, int y, int width, int height)
{
  setRect(&rect, winWidth / width, winHeight / height, (winWidth / width) * x , (winHeight / height) * y);
  SDL_RenderCopy(pRender, wallTexture, NULL, &rect);
}

void SDLLib::drawItem(int x, int y, int width, int height)
{
  setRect(&rect, winWidth / width, winHeight / height, (winWidth / width) * x , (winHeight / height) * y);
  SDL_RenderCopy(pRender, bgTexture, NULL, &rect);
  SDL_RenderCopy(pRender, shroomTexture, NULL, &rect);
}

void SDLLib::drawCharacter(int x, int y, int width, int height, std::string const spriteName)
{
  setRect(&rect, winWidth / width, winHeight / height, (winWidth / width) * x , (winHeight / height) * y);
  SDL_RenderCopy(pRender, bgTexture, NULL, &rect);
  if (spriteName == "ghost")
    SDL_RenderCopy(pRender, ghostTexture, NULL, &rect);
  else if (spriteName == "pacman-right")
    SDL_RenderCopy(pRender, pacmanRightTexture, NULL, &rect);
  else if (spriteName == "pacman-left")
    SDL_RenderCopy(pRender, pacmanLeftTexture, NULL, &rect);
  else if (spriteName == "pacman-down")
    SDL_RenderCopy(pRender, pacmanDownTexture, NULL, &rect);
  else if (spriteName == "pacman-up")
    SDL_RenderCopy(pRender, pacmanUpTexture, NULL, &rect);
  else if (spriteName == "snake")
    SDL_RenderCopy(pRender, snakeTexture, NULL, &rect);
}

void SDLLib::setRect(SDL_Rect *rect, int w, int h, int x, int y)
{
  rect->w = w;
  rect->h = h;
  rect->x = x;
  rect->y = y;
}

int SDLLib::menu()
{
	bool quit = false;
	SDL_Event event;
	int i = 1;
	this->menuUp();
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (event.key.keysym.sym == SDLK_ESCAPE))
				exit(EXIT_SUCCESS);
			if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_RETURN)
				{
					quit = true;
					return (i);
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					if (i == 0)
					{
						this->menuUp();
						i = 1;
					}
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					if (i == 1)
					{
						this->menuDown();
						i = 0;
					}
				}
			}
		}
	}
	SDL_RenderClear(pRender);
	return (1);
}

void SDLLib::clear()
{}

void SDLLib::menuDown()
{
  SDL_RenderCopy(pRender, devosTexture, NULL, NULL);
  setRect(&rect, 100, 100, 100 , 450);
  SDL_RenderCopy(pRender, beerTexture, NULL, &rect);
  setRect(&rect, 500, 200, 200 , 100);
  SDL_RenderCopy(pRender, snakeLogoTexture, NULL, &rect);
  setRect(&rect, 500, 200, 200 , 400);
  SDL_RenderCopy(pRender, pacmanLogoTexture, NULL, &rect);
  SDL_RenderPresent(pRender);
}

void SDLLib::menuUp()
{
  SDL_RenderCopy(pRender, devosTexture, NULL, NULL);
  setRect(&rect, 100, 100, 100 , 150);
  SDL_RenderCopy(pRender, beerTexture, NULL, &rect);
  setRect(&rect, 500, 200, 200 , 100);
  SDL_RenderCopy(pRender, snakeLogoTexture, NULL, &rect);
  setRect(&rect, 500, 200, 200 , 400);
  SDL_RenderCopy(pRender, pacmanLogoTexture, NULL, &rect);
  SDL_RenderPresent(pRender);
}

void SDLLib::initClip()
{
  int clipX = 320 / 5;
  int clipY = 256 / 4;

  clip[UTR].x = 0;
  clip[UTR].y = 0;
  clip[UTR].w = clipX;
  clip[UTR].h = clipY;

  clip[ROL].x = clipX;
  clip[ROL].y = 0;
  clip[ROL].w = clipX;
  clip[ROL].h = clipY;

  clip[RTD].x = 2 * clipX;
  clip[RTD].y = 0;
  clip[RTD].w = clipX;
  clip[RTD].h = clipY;

  clip[HU].x = 3 * clipX;
  clip[HU].y = 0;
  clip[HU].w = clipX;
  clip[HU].h = clipY;

  clip[HR].x = 4 * clipX;
  clip[HR].y = 0;
  clip[HR].w = clipX;
  clip[HR].h = clipY;

  clip[DTR].x = 0;
  clip[DTR].y = clipY;
  clip[DTR].w = clipX;
  clip[DTR].h = clipY;

  clip[DOU].x = 2 * clipX;
  clip[DOU].y = clipY;
  clip[DOU].w = clipX;
  clip[DOU].h = clipY;

  clip[HL].x = 3 * clipX;
  clip[HL].y = clipY;
  clip[HL].h = clipY;
  clip[HL].w = clipX;

  clip[HD].x = 4 * clipX;
  clip[HD].y = clipY;
  clip[HD].w = clipX;
  clip[HD].h = clipY;

  clip[RTL].x = 2 * clipX;
  clip[RTL].y = 2 * clipY;
  clip[RTL].w = clipX;
  clip[RTL].h = clipY;

  clip[TU].x = 3 * clipX;
  clip[TU].y = 2 * clipY;
  clip[TU].w = clipX;
  clip[TU].h = clipY;

  clip[TR].x = 4 * clipX;
  clip[TR].y = 2 * clipY;
  clip[TR].w = clipX;
  clip[TR].h = clipY;

  clip[APPLE].x = 0;
  clip[APPLE].y = 3 * clipY;
  clip[APPLE].w = clipX;
  clip[APPLE].h = clipY;

  clip[TL].x = 3 * clipX;
  clip[TL].y = 3 * clipY;
  clip[TL].w = clipX;
  clip[TL].h = clipY;

  clip[TD].x = 4 * clipX;
  clip[TD].y = 3 * clipY;
  clip[TD].w = clipX;
  clip[TD].h = clipY;
}

extern "C"
{
  IGfx *createLib()
  {
    return new SDLLib(1080, 920);
  }
}
