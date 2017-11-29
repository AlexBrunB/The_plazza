//
// ThreadPool.cpp for ThreadPool in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Thu Apr 20 18:19:13 2017 dEIcIdE
// Last update Thu Apr 27 01:16:32 2017 dEIcIdE
//

#include <condition_variable>
#include <functional>
#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>

#include "ThreadPool.hpp"
#include "Parser.hpp"

FourCheese::ThreadPool::ThreadPool(unsigned int nbThread) : _nbThread(nbThread), _end(false)
{
  unsigned int	i = 0;

  while (i < _nbThread)
    {
      _vecThread.push_back(std::make_shared<std::thread>(&ThreadPool::threadManager, this));
      i++;
    }
}

void		FourCheese::ThreadPool::endThread()
{
  std::lock_guard<std::mutex>	lock(_mutex);

  _end = true;
  _condVar.notify_all();
}

FourCheese::ThreadPool::~ThreadPool()
{
  endThread();
  for (auto &ref : _vecThread)
    ref.get()->join();
}

void		FourCheese::ThreadPool::threadManager()
{
  std::unique_lock<std::mutex>			lock(_mutex);
  std::function<const std::string()>		func;
  std::string					result;

  while (!_end)
    {
      _condVar.wait(lock, [this]{
	  if (_end ||  _taskFunction.empty() == false)
	    return (true);
	  return (false);
	});
      if (_end)
	return ;
      while (!_end && _taskFunction.empty() == false)
	{
	  func = _taskFunction.front();
	  _taskFunction.pop();
	  lock.unlock();
	  result = func();
	  lock.lock();
	  _return.push(result);
	  result = "";
	}
    }
}

bool		FourCheese::ThreadPool::launchTask(std::string const & task)
{
  std::lock_guard<std::mutex>		lock(_mutex);
  auto func = std::bind(&Parser::parse_file, &_parser, task.substr(1), (FourCheese::Information)(task[0] - 48));

  _taskFunction.push(func);
  _condVar.notify_one();
  return (true);
}

bool		FourCheese::ThreadPool::getResult(std::string &result)
{
  std::lock_guard<std::mutex>		lock(_mutex);

  result = "";
  if (_return.empty() == false)
    {
      result = _return.front();
      _return.pop();
      return (true);
    }
  return (false);
}
