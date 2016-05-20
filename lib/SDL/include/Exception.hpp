//
// Exception.hpp for arcade in /home/thomas/rendu/tek2/C++/cpp_arcade/lib/SDL
//
// Made by raout_t
// Login   <thomas@epitech.net>
//
// Started on  Fri Mar 11 13:34:32 2016 raout_t
// Last update Fri Mar 11 13:34:33 2016 raout_t
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
