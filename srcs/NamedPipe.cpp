//
// NamedPipe.cpp for NamedPipe in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 14:49:54 2017 dEIcIdE
// Last update Sat Apr 29 13:01:09 2017 dEIcIdE
//

#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "NamedPipe.hpp"
#include "PlazzaError.hpp"
#include "get_next_line.h"

FourCheese::NamedPipe::NamedPipe()
{
}

FourCheese::NamedPipe::NamedPipe(std::string const & name, bool creat) throw() :
  _name({name + "_in", name + "_out"}), _fdIn(-1), _fdOut(-1)
{
  int	join[2] = {IN, OUT};

  try
    {
      if (creat == true)
	{
	  _creator = true;
	  if (mkfifo(_name[IN].c_str(), RW_ALL) != 0)
	    throw NamedPipeError(std::string("mkfifo : FAIL ") + strerror(errno), 1);
	  if (mkfifo(_name[OUT].c_str(), RW_ALL) != 0)
	    throw NamedPipeError(std::string("mkfifo : FAIL ") + strerror(errno), 2);
	  _fdOut = open(_name[join[OUT]].c_str(), O_RDWR | O_NONBLOCK);
	  _fdIn = open(_name[join[IN]].c_str(), O_RDWR | O_NONBLOCK);
	}
      else
	{
	  _creator = false;
	  join[IN] = OUT;
	  join[OUT] = IN;
	  _fdIn = open(_name[join[IN]].c_str(), O_RDWR | O_NONBLOCK);
	  _fdOut = open(_name[join[OUT]].c_str(), O_RDWR | O_NONBLOCK);
	}
      if (_fdIn == -1)
	throw NamedPipeError("open : FAIL to open the file for input operation", 3);
      if (_fdOut == -1)
	throw NamedPipeError("open : FAIL to open the file for output operation", 3);
    }
  catch (NamedPipeError _error)
    {
      if (_error.getStage() >= 2)
	unlink(_name[IN].c_str());
      if (_error.getStage() == 3)
	unlink(_name[OUT].c_str());
      if (_fdIn != -1)
	close(_fdIn);
      if (_fdOut != -1)
	close(_fdOut);
      throw PlazzaCriticalError(_error.what());
    }
}

FourCheese::NamedPipe::NamedPipe(std::string const & name) throw() :
  _name({name + "_in", name + "_out"}), _fdIn(-1), _fdOut(-1)
{
  int	error = 0;

  try
    {
      _creator = true;
      error = 3;
      if (mkfifo(_name[IN].c_str(), RW_ALL) != 0)
	throw NamedPipeError(std::string("mkfifo : FAIL ") + strerror(errno), 1);
      if (mkfifo(_name[OUT].c_str(), RW_ALL) != 0)
	throw NamedPipeError(std::string("mkfifo : FAIL ") + strerror(errno), 2);
      _fdOut = open(_name[OUT].c_str(), O_RDWR | O_NONBLOCK);
      _fdIn = open(_name[IN].c_str(), O_RDWR | O_NONBLOCK);
      if (_fdIn == -1)
	throw NamedPipeError("open : FAIL to open the file for input operation", error);
      if (_fdOut == -1)
	throw NamedPipeError("open : FAIL to open the file for output operation", error);
    }
  catch (NamedPipeError _error)
    {
      if (_error.getStage() >= 2)
	unlink(_name[IN].c_str());
      if (_error.getStage() == 3)
	unlink(_name[OUT].c_str());
      if (_fdIn != -1)
	close(_fdIn);
      if (_fdOut != -1)
	close(_fdOut);
      throw PlazzaCriticalError(_error.what());
    }
}

FourCheese::NamedPipe::NamedPipe(FourCheese::NamedPipe &&other)
  : _fdIn(-1), _fdOut(-1)
{
  _name[IN] = std::move(other._name[IN]);
  _name[OUT] = std::move(other._name[OUT]);
  _fdIn = std::move(other._fdIn);
  _fdOut = std::move(other._fdOut);
  _creator = std::move(other._creator);

  other._name[IN] = "";
  other._name[OUT] = "";
  other._fdIn = -1;
  other._fdOut = -1;
}

FourCheese::NamedPipe	&FourCheese::NamedPipe::operator=(FourCheese::NamedPipe &&other)
{
  if (this == &other)
    return (*this);
  _name[IN] = std::move(other._name[IN]);
  _name[OUT] = std::move(other._name[OUT]);
  _fdIn = std::move(other._fdIn);
  _fdOut = std::move(other._fdOut);
  _creator = std::move(other._creator);

  other._name[IN] = "";
  other._name[OUT] = "";
  other._fdIn = -1;
  other._fdOut = -1;
  return (*this);
}

FourCheese::NamedPipe::~NamedPipe()
{
  close(_fdIn);
  close(_fdOut);
  if (_creator == true)
    {
      unlink(_name[IN].c_str());
      unlink(_name[OUT].c_str());
    }
}

void	FourCheese::NamedPipe::swapFd()
{
  int	tmp;

  tmp = _fdIn;
  _fdIn = _fdOut;
  _fdOut = tmp;
}

bool				FourCheese::NamedPipe::sendMsg(std::string const & msgSend) const
{
  write(_fdOut, msgSend.c_str(), msgSend.length());
  return (true);
}

std::string const &		FourCheese::NamedPipe::receivMsg(std::string &msgReceived) const
{
  char				*buff;

  buff = get_next_line(_fdIn);
  if (buff != NULL)
    msgReceived = std::string(buff);
  else
    msgReceived = "";
  free(buff);
  return (msgReceived);
}

bool				FourCheese::NamedPipe::operator<<(std::string const & msgSend) const
{
  return (sendMsg(msgSend));
}

std::string const &		FourCheese::NamedPipe::operator>>(std::string & msgReceived) const
{
  return (receivMsg(msgReceived));
}
