//
// NamedPipe.cpp for NamedPipe in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 14:49:54 2017 dEIcIdE
// Last update Mon Apr 17 23:59:08 2017 dEIcIdE
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

NamedPipe::NamedPipe()
{
}

NamedPipe::NamedPipe(std::string const & name, bool creat) throw() :
  _name({name + "_in", name + "_out"}), _fdIn(-1), _fdOut(-1)
{
  int	error = 0;
  int	join[2] = {IN, OUT};

  try
    {
      if (creat == true)
	{
	  _creator = true;
	  error = 3;
	  if (mkfifo(_name[IN].c_str(), RW_ALL) != 0)
	    throw NamedPipeError(std::string("mkfifo : FAIL ") + strerror(errno), 1);
	  if (mkfifo(_name[OUT].c_str(), RW_ALL) != 0)
	    throw NamedPipeError(std::string("mkfifo : FAIL ") + strerror(errno), 2);
	  _fdOut = open(_name[join[OUT]].c_str(), O_WRONLY);
	  sleep(1);
	  _fdIn = open(_name[join[IN]].c_str(), O_RDONLY);
	}
      else
	{
	  _creator = false;
	  join[IN] = OUT;
	  join[OUT] = IN;
	  _fdIn = open(_name[join[IN]].c_str(), O_RDONLY);
	  _fdOut = open(_name[join[OUT]].c_str(), O_WRONLY);
	}
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

NamedPipe::~NamedPipe()
{
  close(_fdIn);
  close(_fdOut);
  if (_creator == true)
    {
      unlink(_name[IN].c_str());
      unlink(_name[OUT].c_str());
    }
}

bool				NamedPipe::sendMsg(std::string const & msgSend)
{
  write(_fdOut, msgSend.c_str(), msgSend.length());
  return (true);
}

std::string const &		NamedPipe::receivMsg(std::string &msgReceived)
{
  char				*buff;

  buff = get_next_line(_fdIn);
  msgReceived = std::string(buff);
  free(buff);
  return (msgReceived);
}

bool				NamedPipe::operator<<(std::string const & msgSend)
{
  return (sendMsg(msgSend));
}

std::string const &		NamedPipe::operator>>(std::string & msgReceived)
{
  return (receivMsg(msgReceived));
}
