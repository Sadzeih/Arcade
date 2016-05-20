//
// GLLib.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/lib/OpenGL/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 13:57:34 2016 Alexis Guerville
// Last update Sun Apr  3 15:54:26 2016 Alexis Guerville
//

#ifndef GLLIB_HPP_
#define GLLIB_HPP_

#include <string>
#include <ctime>
#include <map>
#include "GL/glew.h"
#include "SFML/OpenGL.hpp"
#include "SFML/Window.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "IGfx.hpp"
#include "Shader.hpp"

class GLLib: public IGfx
{
	sf::RenderWindow *_window;
	GLuint _shaderProgram;
	Shader *_vertexShader;
	Shader *_fragmentShader;
	GLuint _ebo;
	GLuint _vbo;
	GLuint _vao;
	GLuint _tex[10];
	glm::mat4 _proj;
	glm::mat4 _model;
	glm::mat4 _view;

	void loadGL();
	void shaders();
	void buffers();
	void textures();
	void loadTexture(std::string const &, int nbT);
public:
	enum Textures
	{
		DEVOS = 0,
		SNAKE = 1,
		CASE = 2,
		WALL = 3,
		ITEM = 4,
		PACMAN = 5,
		MENU = 6,
		MAXIMATOR = 7,
		GHOST = 8,
		PASTILLE = 9,
	};

	GLLib(int width, int height);
	~GLLib();

	void clear();
	void display(struct timeval&);
	void drawTextureScreen(GLfloat*, int, GLuint*, int, int);
	void drawCase(int width, int height, int, int);
	void drawWall(int width, int height, int, int);
	void drawItem(int width, int height, int, int);
	void drawPastille(int, int, int, int);
	void drawCharacter(int, int, int, int, std::string const);
	void drawPacman(int, int, int, int, int);
	int getEvent();
	int menu();
	double getTimeDiff(struct timeval pTime) const;
	void getTime(struct timeval *pTime) const;
};

#endif
