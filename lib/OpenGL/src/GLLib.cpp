//
// GLLib.cpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/lib/OpenGL/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 14:26:12 2016 Alexis Guerville
// Last update Sun Apr  3 15:54:59 2016 Alexis Guerville
//

#include <string>
#include <chrono>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <sys/time.h>
#include <cstring>
#include <unistd.h>
#include "GL/glew.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GLLib.hpp"
#include "Exception.hpp"
#include "Shader.hpp"

GLLib::GLLib(int width, int height)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	_window = new sf::RenderWindow(sf::VideoMode(width, height), "Arcade", sf::Style::Default, settings);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
  	throw Exception("Failed to initialize GLEW");
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	buffers();
}

GLLib::~GLLib()
{
	glDeleteProgram(_shaderProgram);
	delete _fragmentShader;
	delete _vertexShader;

	glDeleteBuffers(1, &_ebo);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(10, _tex);

	glDeleteVertexArrays(1, &_vao);
	delete _window;
}

void GLLib::buffers()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glGenTextures(10, _tex);
}

void GLLib::textures()
{
	static int lol = 0;

	if (lol == 0)
	{
		loadTexture("devos.jpg", DEVOS);
		loadTexture("./lib/OpenGL/snake.jpg", SNAKE);
		loadTexture("./lib/OpenGL/sand.jpg", CASE);
		loadTexture("./lib/OpenGL/wall.png", WALL);
		loadTexture("./lib/OpenGL/apple.jpg", ITEM);
		loadTexture("./lib/OpenGL/pacman.jpg", PACMAN);
		loadTexture("./lib/OpenGL/menu.png", MENU);
		loadTexture("beer-maximator.png", MAXIMATOR);
		loadTexture("./lib/OpenGL/booface.jpg", GHOST);
		loadTexture("./lib/OpenGL/pastille.jpg", PASTILLE);
		lol = 1;
	}
}

void GLLib::loadTexture(std::string const &path, int nbT)
{
	sf::Image image;
	if (!image.loadFromFile(path))
	{
		if (!image.loadFromFile("devos.jpg"))
			throw Exception("Could not load '%s'"+ path);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex[nbT]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glUniform1i(glGetUniformLocation(_shaderProgram, "tex"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void GLLib::shaders()
{
	GLint success;
	GLchar infoLog[512];

	_vertexShader = new Shader("./lib/OpenGL/shaders/vertexshader.glsl", GL_VERTEX_SHADER);
	_vertexShader->load();
	_vertexShader->compile();

	_fragmentShader = new Shader("./lib/OpenGL/shaders/fragmentshader.glsl", GL_FRAGMENT_SHADER);
	_fragmentShader->load();
	_fragmentShader->compile();

	_shaderProgram = glCreateProgram();
	_vertexShader->link(_shaderProgram);
	_fragmentShader->link(_shaderProgram);
	glBindFragDataLocation(_shaderProgram, 0, "outColor");
	glLinkProgram(_shaderProgram);
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
		std::string error = infoLog;
		throw Exception("Shader compilation error:\n" + error);
	}
	glUseProgram(_shaderProgram);

	GLint posAttrib = glGetAttribLocation(_shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,\
		8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(posAttrib);

	GLint colAttrib = glGetAttribLocation(_shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,\
		8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	GLint texAttrib = glGetAttribLocation(_shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
		8 * sizeof(GLfloat), (GLfloat*)(6 * sizeof(GLfloat)));

	GLint uniModel = glGetUniformLocation(_shaderProgram, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(_model));

	_proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 1.0f, 1000.0f);
	GLint uniProj = glGetUniformLocation(_shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(_proj));

	// _view = glm::lookAt(
	//     glm::vec3(0.0f, 2.5f, -1.0f),
	//     glm::vec3(0.0f, 0.0f, 0.0f),
	//     glm::vec3(0.0f, 0.0f, 1.0f)
	// );
	_view = glm::rotate(
			_view,
			glm::radians(90.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
	);

	GLint uniView = glGetUniformLocation(_shaderProgram, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(_view));
}

int GLLib::getEvent()
{
	sf::Event event;

	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			return (IGfx::QUIT);
		else if (event.type == sf::Event::Resized)
			glViewport(0, 0, event.size.width, event.size.height);
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				return (IGfx::QUIT);
			if (event.key.code == sf::Keyboard::Right)
				return (IGfx::RIGHT);
			else if (event.key.code == sf::Keyboard::Left)
				return (IGfx::LEFT);
			else if (event.key.code == sf::Keyboard::Up)
				return (IGfx::UP);
			else if (event.key.code == sf::Keyboard::Down)
				return (IGfx::DOWN);
		}
		else if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode == '&')
				return (IGfx::NEXT_GAME);
			else if (event.text.unicode == 233)
				return (IGfx::PREV_GAME);
			else if (event.text.unicode == '\"')
				return (IGfx::NEXT_LIB);
			else if (event.text.unicode == '\'')
				return (IGfx::PREV_LIB);
			else if (event.text.unicode == '(')
				return (IGfx::RESTART);
			else if (event.text.unicode == '-')
				return (IGfx::MENU);
		}
	}
	return IGfx::NOTHING;
}

double GLLib::getTimeDiff(struct timeval pTime) const
{
	double timeDiff;
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		throw Exception(std::strerror(errno));
	timeDiff = (tv.tv_sec - pTime.tv_sec) * 1000.0;
  timeDiff += (tv.tv_usec - pTime.tv_usec) / 1000.0;
	return timeDiff;
}

void GLLib::getTime(struct timeval *pTime) const
{
	if (gettimeofday(pTime, NULL) == -1)
		throw Exception(std::strerror(errno));
}

void GLLib::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLLib::display(struct timeval &pTime)
{
	if (getTimeDiff(pTime) < 16)
		return;
	getTime(&pTime);
	shaders();
	textures();
	_window->display();
}

void GLLib::drawPastille(int width, int height, int widthMap, int heightMap)
{
	GLfloat widthStep;
	if (widthMap != 0)
		widthStep = (2 / (float)widthMap);
	else
		widthStep = 0;
	GLfloat heightStep;
	if (heightMap != 0)
		heightStep = (2 / (float)heightMap);
	else
		heightStep = 0;
	height++;

	glm::mat4 trans;
	_model = glm::rotate(
		trans,
		glm::radians(0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);

	GLfloat vertices[] = {
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f,	1.0f, 1.0f, 1.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f,	1.0f,	1.0f, 0.0f, 1.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f,	1.0f,	1.0f, 0.0f, 0.0f,
	};
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};
	glEnable(GL_DEPTH_TEST);
	drawTextureScreen(vertices, 4*6, elements, 36, (int)PASTILLE);
}

void GLLib::drawCase(int width, int height, int widthMap, int heightMap)
{
	GLfloat widthStep;
	if (widthMap != 0)
		widthStep = (2 / (float)widthMap);
	else
		widthStep = 0;
	GLfloat heightStep;
	if (heightMap != 0)
		heightStep = (2 / (float)heightMap);
	else
		heightStep = 0;
	height++;

	glm::mat4 trans;
	_model = glm::rotate(
		trans,
		glm::radians(0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);

	GLfloat vertices[] = {
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f,	1.0f, 1.0f, 1.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f,	1.0f,	1.0f, 0.0f, 1.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f,	1.0f,	1.0f, 0.0f, 0.0f,
	};
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};
	glEnable(GL_DEPTH_TEST);
	drawTextureScreen(vertices, 4*6, elements, 36, (int)CASE);
}

void GLLib::drawWall(int width, int height, int widthMap, int heightMap)
{
	GLfloat widthStep;
	if (widthMap != 0)
		widthStep = (2 / (float)widthMap);
	else
		widthStep = 0;
	GLfloat heightStep;
	if (heightMap != 0)
		heightStep = (2 / (float)heightMap);
	else
		heightStep = 0;
	height++;

	GLfloat vertices[] = {
		//front
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//top
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//back
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f, (float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		// bottom
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//left
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//Right
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f,	1.0f,	1.0f, 0.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	};
	GLuint elements[] = {
		// front
     0,  1,  2,
     2,  3,  0,
    // top
     4,  5,  6,
     6,  7,  4,
    // back
     8,  9, 10,
    10, 11,  8,
    // bottom
    12, 13, 14,
    14, 15, 12,
    // left
    16, 17, 18,
    18, 19, 16,
    // right
    20, 21, 22,
    22, 23, 20,
	};
	glEnable(GL_DEPTH_TEST);
	drawTextureScreen(vertices, 4*6, elements, 36, (int)WALL);
}

void GLLib::drawItem(int width, int height, int widthMap, int heightMap)
{
	GLfloat widthStep;
	if (widthMap != 0)
		widthStep = (2 / (float)widthMap);
	else
		widthStep = 0;
	GLfloat heightStep;
	if (heightMap != 0)
		heightStep = (2 / (float)heightMap);
	else
		heightStep = 0;
	height++;
	GLfloat vertices[] = {
		//front
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//top
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//back
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f, (float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		// bottom
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//left
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//Right
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	};
	glm::mat4 trans;
	_model = glm::rotate(
			trans,
			glm::radians(0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
	);
	GLuint elements[] = {
		// front
     0,  1,  2,
     2,  3,  0,
    // top
     4,  5,  6,
     6,  7,  4,
    // back
     8,  9, 10,
    10, 11,  8,
    // bottom
    12, 13, 14,
    14, 15, 12,
    // left
    16, 17, 18,
    18, 19, 16,
    // right
    20, 21, 22,
    22, 23, 20,
	};
	drawTextureScreen(vertices, 4*6, elements, 36, (int)ITEM);
}

void GLLib::drawCharacter(int width, int height, int widthMap, int heightMap, std::string const spriteName)
{
	(void)spriteName;
	GLfloat widthStep;
	if (widthMap != 0)
		widthStep = (2 / (float)widthMap);
	else
		widthStep = 0;
	GLfloat heightStep;
	if (heightMap != 0)
		heightStep = (2 / (float)heightMap);
	else
		heightStep = 0;
	height++;

	GLfloat vertices[] = {
		//front
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//top
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//back
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f, (float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		// bottom
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//left
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)(-1 + ((float)width * widthStep)),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		//Right
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.0f,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)((1 - ((float)height * heightStep)) + heightStep),
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		heightStep,
		(float)((-1 + ((float)width * widthStep)) + widthStep),
		(float)(1 - ((float)height * heightStep)),
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	};
	glm::mat4 trans;
	_model = glm::rotate(
	    trans,
	    glm::radians(0.0f),
	    glm::vec3(0.0f, 0.0f, 1.0f)
	);
	GLuint elements[] = {
		// front
     0,  1,  2,
     2,  3,  0,
    // top
     4,  5,  6,
     6,  7,  4,
    // back
     8,  9, 10,
    10, 11,  8,
    // bottom
    12, 13, 14,
    14, 15, 12,
    // left
    16, 17, 18,
    18, 19, 16,
    // right
    20, 21, 22,
    22, 23, 20,
	};
	glEnable(GL_DEPTH_TEST);
	if (spriteName == "square.png")
	{
		_view = glm::lookAt(
				glm::vec3(0.0f, 1.0f, -1.0f),
				glm::vec3(-(float)(-1 + ((float)width * widthStep)), -(float)(-1 + ((float)height * heightStep)), 0.5f),
				glm::vec3(0.0f, 1.0f, 0.0f)
		);
		drawTextureScreen(vertices, 4*6, elements, 36, (int)SNAKE);
	}
	else if (spriteName.find("pacman") != std::string::npos)
	{
		_view = glm::lookAt(
				glm::vec3(0.0f, 2.0f, -0.5f),
				glm::vec3(-(float)(-1 + ((float)width * widthStep)), -(float)(-1 + ((float)height * heightStep)), 0.5f),
				glm::vec3(0.0f, 1.0f, 0.0f)
		);
		drawTextureScreen(vertices, 4*6, elements, 36, (int)PACMAN);
	}
	else if (spriteName == "ghost")
		drawTextureScreen(vertices, 4*6, elements, 36, (int)GHOST);
	else
		drawTextureScreen(vertices, 4*6, elements, 36, (int)DEVOS);
}

void GLLib::drawTextureScreen(GLfloat *vertices, int nbV, GLuint *elements, int nbE, int tex)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _tex[tex]);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * nbV * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements) * nbE * sizeof(GLuint), elements, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, nbE, GL_UNSIGNED_INT, 0);
}

int GLLib::menu()
{
	sf::Event event;
	struct timeval start;
	getTime(&start);
	int i = 0;
	glm::mat4 francis;

	bool running = true;
	while (running)
	{
		while (_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				delete _window;
				exit(1);
			}
			else if (event.type == sf::Event::Resized)
				glViewport(0, 0, event.size.width, event.size.height);
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					delete _window;
					exit(1);
				}
				if (event.key.code == sf::Keyboard::Up)
					i = 0;
				else if (event.key.code == sf::Keyboard::Down)
					i = 1;
				if (event.key.code == sf::Keyboard::Return)
					return (i);
			}
		}
		clear();
		textures();
		GLuint elements[] = {
			 0,  1,  2,
			 2,  3,  0,
		};
		GLfloat vertices[] = {
			-1.0f, 1.0f, 1.0f, 1.0f * (float)glm::sin(getTimeDiff(start) / 500) + 0.1f, 1.0f * ((float)glm::sin(getTimeDiff(start) / 300) + 0.5f), 1.0f * ((float)glm::sin(getTimeDiff(start) / 200) + 0.1f), 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f * (float)glm::sin(getTimeDiff(start) / 230) + 0.1f, 1.0f * ((float)glm::sin(getTimeDiff(start) / 1000) + 0.5f), 1.0f * ((float)glm::sin(getTimeDiff(start) / 130) + 0.1f), 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 1.0f * (float)glm::sin(getTimeDiff(start) / 640) + 0.1f, 1.0f * ((float)glm::sin(getTimeDiff(start) / 100) + 0.5f), 1.0f * ((float)glm::sin(getTimeDiff(start) / 100) + 0.1f), 0.0f, 1.0f,
			-1.0f, -1.0f, 1.0f, 1.0f * (float)glm::sin(getTimeDiff(start) / 1000) + 0.1f, 1.0f * ((float)glm::sin(getTimeDiff(start) / 50) + 0.5f), 1.0f * ((float)glm::sin(getTimeDiff(start) / 4000) + 0.1f), 0.0f, 0.0f,
		};
		float timeDiff = (float)(getTimeDiff(start) / 20000);
		francis = glm::rotate(
				francis,
				timeDiff * glm::radians(10.0f),
				glm::vec3(0.0f, 0.0f, 1.0f)
		);
		GLint model = glGetUniformLocation(_shaderProgram, "model");
		glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(francis));
		drawTextureScreen(vertices, 4, elements, 6, DEVOS);


		glm::mat4 trans;
		// _model = trans;
		_model = glm::rotate(
				trans,
				glm::radians(90.0f),
				glm::vec3(0.0f, 0.0f, 1.0f)
		);
		glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(_model));
		GLfloat verticesMenu[] = {
			-0.5f, 0.5f, 1.001f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 1.001f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 1.001f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 1.001f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		drawTextureScreen(verticesMenu, 4, elements, 6, (int)MENU);

		glm::mat4 maximator;
		maximator = glm::rotate(
				trans,
				glm::radians(90.0f),
				glm::vec3(0.0f, 0.0f, 0.5f)
		);
		maximator = glm::translate(
			maximator,
			glm::vec3(-0.01f + ((float)i / 7), -0.4f, 0.0f)
		);
		GLint lol = glGetUniformLocation(_shaderProgram, "model");
		glUniformMatrix4fv(lol, 1, GL_FALSE, glm::value_ptr(maximator));
		GLfloat verticesSelector[] = {
			-0.08f, 0.08f, 1.002f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			0.08f, 0.08f, 1.002f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.08f, -0.08f, 1.002f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.08f, -0.08f, 1.002f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		};
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		drawTextureScreen(verticesSelector, 4, elements, 6, MAXIMATOR);

		shaders();
		_view = glm::lookAt(
				glm::vec3(0.0f, 0.1f, 2.2f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 1.0f)
		);

		GLint uniView = glGetUniformLocation(_shaderProgram, "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(_view));

		_window->display();
	}
	return (1);
}

extern "C"
{
	IGfx *createLib()
	{
		return new GLLib(1280, 720);
	}
}
