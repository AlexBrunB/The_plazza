//
// Process.cpp for Process in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Wed Apr 19 11:33:54 2017 dEIcIdE
// Last update Wed Apr 19 19:02:54 2017 dEIcIdE
//

#include <map>
#include <iostream>
#include <unistd.h>

#include "Process.hpp"
#include "NamedPipe.hpp"
#include "PlazzaError.hpp"

FourCheese::Process::Process() :
  _id(0)
{
}

FourCheese::Process::~Process()
{
  for (auto it = _com.begin(); it != _com.end();)
    {
      it->second.reset();
      it = _com.erase(it);
    }
}

bool		FourCheese::Process::launchProcess()
{
  unsigned int	i = 1;
  pid_t		pid;

  for (auto &it : _com)
    {
      if (i == it.first)
	i++;
    }
  try
    {
      _com[i] = std::make_unique<FourCheese::NamedPipe>("./fifo/TheGreatPipe" + std::to_string(i));
    }
  catch (FourCheese::PlazzaCriticalError _error)
    {
      return (false);
    }
  if ((pid = fork()) == -1)
    return (false);
  if (pid == 0)
    {
      _id = i;
      _com[_id]->swapFd();
      clean();
      soonAction();
      exit (0);
    }
  return (true);
}

void	FourCheese::Process::clean()
{
  for (auto it = _com.begin(); it != _com.end();)
    {
      if (it->first != _id)
	{
	  it->second.reset();
	  it = _com.erase(it);
	}
      else
	it++;
    }
}

void	FourCheese::Process::soonAction()
{
  std::string	tmp;

  std::cout << "test : " << _id << std::endl;
  *(_com[_id]) << "Je suis bien crée, prée a dominée le monde !!\n";
  *(_com[_id]) >> tmp;
  while (tmp.compare("Job done") != 0)
    *(_com[_id]) >> tmp;
  *(_com[_id]) << "Done\n";
  std::cout << tmp << " filse done " << std::endl;
}

