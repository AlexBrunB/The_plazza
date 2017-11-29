//
// PlazzaError.cpp for PlazzaError in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 16:58:26 2017 dEIcIdE
// Last update Sun Apr 16 17:57:13 2017 dEIcIdE
//

#include <exception>
#include <string>

#include "PlazzaError.hpp"

PlazzaError::PlazzaError(std::string const & errorMsg) throw() :
  _errorMsg(errorMsg)
{
}

PlazzaError::~PlazzaError() throw()
{
}

const char	*PlazzaError::what() const throw()
{
  return (_errorMsg.c_str());
}

NamedPipeError::NamedPipeError(std::string const & errorMsg, int stage) throw() :
  PlazzaError(errorMsg), _stage(stage)
{
}

NamedPipeError::~NamedPipeError() throw()
{
}

int		NamedPipeError::getStage() const
{
  return (_stage);
}

PlazzaCriticalError::PlazzaCriticalError(std::string const & errorMsg) throw() :
  PlazzaError(errorMsg)
{
}

PlazzaCriticalError::~PlazzaCriticalError() throw()
{
}
