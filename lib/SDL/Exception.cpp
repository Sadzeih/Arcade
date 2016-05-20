//
// Exception.cpp for arcade in /home/devos-f/Documents/Projet/cpp_arcade/src/
//
// Made by François Devos
// Login   <devos_f@epitech.eu>
//
// Started on  Thu Mar 10 13:18:25 2016 François Devos
// Last update Fri Mar 11 17:21:40 2016 Alexis Guerville
//

#include <string>
#include "Exception.hpp"

Exception::Exception(std::string const& message) throw()
: message(message)
{

}

Exception::~Exception() throw()
{

}

const char* Exception::what() const throw()
{
  return (this->message.c_str());
}
