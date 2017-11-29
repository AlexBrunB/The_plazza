//
// PlazzaError.cpp for PlazzaError in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 16:58:26 2017 dEIcIdE
// Last update Tue Apr 18 16:45:03 2017 dEIcIdE
//

#include <exception>
#include <string>

#include "PlazzaError.hpp"

FourCheese::PlazzaError::PlazzaError(std::string const & errorMsg) throw() :
  _errorMsg(errorMsg)
{
}

FourCheese::PlazzaError::~PlazzaError() throw()
{
}

const char	*FourCheese::PlazzaError::what() const throw()
{
  return (_errorMsg.c_str());
}

FourCheese::NamedPipeError::NamedPipeError(std::string const & errorMsg, int stage) throw() :
  PlazzaError(errorMsg), _stage(stage)
{
}

FourCheese::NamedPipeError::~NamedPipeError() throw()
{
}

int		FourCheese::NamedPipeError::getStage() const
{
  return (_stage);
}

FourCheese::PlazzaCriticalError::PlazzaCriticalError(std::string const & errorMsg) throw() :
  PlazzaError(errorMsg)
{
}

FourCheese::PlazzaCriticalError::~PlazzaCriticalError() throw()
{
}
