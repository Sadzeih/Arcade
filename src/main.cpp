//
// main.cpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/src/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 13:04:39 2016 Alexis Guerville
// Last update Mon Mar 28 14:10:28 2016 Alexis Guerville
//

#include <string>
#include <iostream>
#include "Exception.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
	std::string lib;
	Core *core;

	try
	{
		if (ac != 2)
			throw Exception("Usage: ./arcade {path to a gfx library}");
		lib = av[1];
		core = new Core(lib);
		core->load();
	}
	catch(std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
