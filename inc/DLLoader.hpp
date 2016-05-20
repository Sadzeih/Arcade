//
// DLLoader.hpp for cpp_arcade in /home/guervi-a/rendu/CPP/cpp_arcade/
//
// Made by Alexis Guerville
// Login   <guervi_a@epitech.eu>
//
// Started on  Thu Mar 10 11:50:04 2016 Alexis Guerville
// Last update Thu Mar 31 15:18:55 2016 Alexis Guerville
//

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include <string>
#include <iostream>

template <typename T>
class DLLoader
{
	std::string _path;
	void *_handle;
public:
	DLLoader(std::string const &path)
	{
		_path = path;
		_handle = dlopen(_path.c_str(), RTLD_NOW);
		if (_handle == NULL)
		{
			std::string error = dlerror();
			throw Exception(error);
		}
	}

	~DLLoader()
	{
		if (dlclose(_handle) != 0)
			throw Exception("Could not close library.");
	}

	DLLoader(DLLoader const &copy)
	{
		_path = copy._path;
		_handle = dlopen(_path.c_str(), RTLD_NOW);
		if (_handle == NULL)
			throw Exception("Library could not be opened.");
	}

	DLLoader &operator=(DLLoader const &copy)
	{
		if (&copy != this)
		{
			_handle = copy._handle;
		}
		return *this;
	}

	T *getInstance(std::string entry_point, int width = 20, int height = 20)
	{
		T	*(*ptr)(int, int);
		ptr = reinterpret_cast<T *(*)(int, int)>(dlsym(_handle, entry_point.c_str()));
      if (ptr == NULL)
			return (NULL);
		return ptr(width, height);
	}
};

#endif
