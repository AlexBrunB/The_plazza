//
// Process.cpp for Process in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Wed Apr 19 11:33:54 2017 dEIcIdE
// Last update Sat Apr 29 13:03:19 2017 dEIcIdE
//

#include <map>
#include <iostream>
#include <unistd.h>
#include <ctime>

#include "Process.hpp"
#include "NamedPipe.hpp"
#include "ThreadPool.hpp"
#include "PlazzaError.hpp"

FourCheese::Process::Process(unsigned int nbThread) :
  _id(0), _nbThread(nbThread)
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

int		FourCheese::Process::launchProcess()
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
      return (-1);
    }
  if ((pid = fork()) == -1)
    return (-1);
  if (pid == 0)
    {
      _id = i;
      _com[_id]->swapFd();
      clean();
      soonAction();
      *(_com[_id]) << "ENDCOM\n";
      exit(0);
    }
  return (i);
}

bool	FourCheese::Process::endProcess(unsigned int idTarget)
{
  if (_com.find(idTarget) == _com.end())
    return (false);
  *(_com[idTarget]) << "ENDCOM\n";
  _com[idTarget].reset();
  _com.erase(idTarget);
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

bool				FourCheese::Process::checkTime(int task)
{
  static std::time_t		startToWait = 0;

  if (task == 0)
    {
      if (startToWait == 0)
	startToWait = std::time(nullptr);
      else if (std::time(nullptr) > startToWait + 4)
	return (false);
    }
  else
    startToWait = 0;
  return (true);
}

void				FourCheese::Process::soonAction()
{
  std::string			tmp;
  std::string			tmp2;
  FourCheese::ThreadPool	pool(_nbThread);
  int				i = 0;

  *(_com[_id]) >> tmp;
  while (tmp.compare("ENDCOM") != 0 && checkTime(i))
    {
      if (tmp != "")
	{
	  i++;
	  pool.launchTask(tmp);
	}
      while (pool.getResult(tmp2))
	{
	  i--;
	  tmp2 += "\n";
	  *(_com[_id]) << tmp2;
	}
      *(_com[_id]) >> tmp;
      usleep(5);
    }
  *(_com[_id]) << "ENDCOM\n";
}

bool				FourCheese::Process::sendMsgTo(std::string const & msgSend, unsigned int idTarget)
{
  return (*(_com[idTarget]) << msgSend);
}

std::string const &		FourCheese::Process::receivMsgFrom(std::string & msg, unsigned int idTarget)
{
  return (*(_com[idTarget]) >> msg);
}
