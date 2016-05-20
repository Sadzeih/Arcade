//
// Shader.cpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/lib/OpenGL/src/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 17 14:09:37 2016 Alexis Guerville
// Last update Thu Mar 17 15:48:34 2016 Alexis Guerville
//

#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "Shader.hpp"
#include "Exception.hpp"

Shader::Shader(std::string const &path, GLenum type)
: _path(path)
{
	_shader = glCreateShader(type);
}

Shader::~Shader()
{
	glDeleteShader(_shader);
}

Shader::Shader(Shader const &copy)
: _shader(copy._shader), _path(copy._path)
{
}

Shader &Shader::operator=(Shader const &copy)
{
	_path = copy._path;
	_shader = copy._shader;
	return *this;
}

std::string Shader::getShaderText()
{
	std::string shader = "";

	std::ifstream shaderFile (_path.c_str() , std::ios::in);
	if(shaderFile.is_open())
	{
		std::string buffer;
		while(getline(shaderFile, buffer))
			shader += buffer + "\n";
		shaderFile.close();
	}
	else
		throw Exception("Couldn't open shader file.");
	return shader;
}

void Shader::load()
{
	std::string shaderText = getShaderText();
	const GLchar *ShaderSource = reinterpret_cast<const GLchar *>(shaderText.c_str());
	glShaderSource(_shader, 1, &ShaderSource, NULL);
}

void Shader::compile()
{
	GLint success;
	GLchar infoLog[512];

	glCompileShader(_shader);
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_shader, 512, NULL, infoLog);
		std::string error = infoLog;
		throw Exception("Shader compilation error in " + _path + ":\n" + error);
	}
}

void Shader::link(GLuint shaderProgram)
{
	glAttachShader(shaderProgram, _shader);
}
