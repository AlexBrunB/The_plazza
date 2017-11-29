//
// ThreadPool.cpp for ThreadPool in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Thu Apr 20 18:19:13 2017 dEIcIdE
// Last update Mon Apr 24 17:12:45 2017 dEIcIdE
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

/*
std::vector<FourCheese::ThreadData>	FourCheese::ThreadPool::_vecData;

FourCheese::ThreadData::ThreadData() : _id(0), _task(ThreadTask::FREE)
{
}

FourCheese::ThreadData::ThreadData(FourCheese::ThreadData &&other) :
  _id(0), _task(ThreadTask::FREE)
{
  std::lock_guard<std::mutex>	lock(other._mutex);

  _id = std::move(other._id);
  _taskFunction = std::move(other._taskFunction);
  _return = std::move(other._return);
  _task = other._task;

  other._id = 0;
  other._task = ThreadTask::END;
}

FourCheese::ThreadData &FourCheese::ThreadData::operator=(FourCheese::ThreadData &&other)
{
  std::unique_lock<std::mutex>	lock_this(_mutex, std::defer_lock);
  std::unique_lock<std::mutex>	lock_other(other._mutex, std::defer_lock);

  if (this == &other)
    return (*this);
  std::lock(lock_this, lock_other);
  _id = std::move(other._id);
  _taskFunction = std::move(other._taskFunction);
  _return = std::move(other._return);
  _task = other._task;

  other._id = 0;
  other._task = ThreadTask::END;
  return (*this);
}
*/
FourCheese::ThreadPool::ThreadPool(unsigned int nbThread) : _nbThread(nbThread), _end(false)
{
  unsigned int	i = 0;

  while (i < _nbThread)
    {
      _vecThread.push_back(std::make_shared<std::thread>(&ThreadPool::threadManager, this, i));
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

void		FourCheese::ThreadPool::threadManager(int id)
{
  std::unique_lock<std::mutex>			lock(_mutex);
  std::function<std::string()>			func;
  std::string					result;

  std::cout << "Welcom in the thread" << std::endl;
  while (!_end)
    {
      _condVar.wait(lock, [this]{
	  if (_end ||  _taskFunction.empty() == false)
	    return (true);
	  return (false);
	});
      if (_end)
	{
	  std::cout << "Go dodo id : " << id << std::endl;
	  return ;
	}
      while (!_end && _taskFunction.empty() == false)
	{
	  func = _taskFunction.front();
	  _taskFunction.pop();
	  lock.unlock();
	  result = func();
	  std::cout << "exec by id : " << id << std::endl;
	  lock.lock();
	  _return.push(result);
	}
    }
}

bool		FourCheese::ThreadPool::launchTask(std::string const & task)
{
  std::lock_guard<std::mutex>		lock(_mutex);
  auto func = std::bind([](std::string lol)->std::string {std::cout << lol << std::endl; return (lol);}, task);
  
  _taskFunction.push(func);
  _condVar.notify_one();
  std::cout << "Task send" << std::endl;
  return (true);
}

bool		FourCheese::ThreadPool::getResult(std::string &result)
{
  std::lock_guard<std::mutex>		lock(_mutex);

  if (_return.empty() == false)
    {
      result = _return.front();
      _return.pop();
      return (true);
    }
  return (false);
}
