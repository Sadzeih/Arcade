//
// Shader.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/lib/OpenGL/include/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 17 14:06:15 2016 Alexis Guerville
// Last update Thu Mar 17 15:48:24 2016 Alexis Guerville
//

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>

class Shader
{
	GLuint _shader;
	std::string _path;

public:
	Shader(std::string const &path, GLenum type);
	~Shader();

	Shader(Shader const &copy);
	Shader &operator=(Shader const &copy);

	std::string getShaderText();
	void load();
	void compile();
	void link(GLuint shaderProgram);
};

#endif
