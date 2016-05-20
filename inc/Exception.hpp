//
// Exception.hpp for exception in /home/devos-f/Documents/Projet/cpp_arcade/inc/
//
// Made by François Devos
// Login   <devos_f@epitech.eu>
//
// Started on  Thu Mar 10 13:18:38 2016 François Devos
// Last update Mon Mar 28 10:45:08 2016 Thomas Raout
//

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <string>
#include <exception>

class Exception : public std::exception
{
  std::string message;
  public:
  Exception(std::string const&) throw();
  ~Exception() throw();
  const char *what() const throw();
};

#endif
