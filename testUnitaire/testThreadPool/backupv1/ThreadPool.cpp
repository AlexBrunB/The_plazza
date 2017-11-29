//
// ThreadPool.cpp for ThreadPool in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Thu Apr 20 18:19:13 2017 dEIcIdE
// Last update Sun Apr 23 01:01:32 2017 dEIcIdE
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

FourCheese::ThreadPool::ThreadPool(unsigned int nbThread) : _nbThread(nbThread)
{
  unsigned int	i = 0;

  _vecData.resize(_nbThread);
  while (i < _nbThread)
    {
      _vecThread.push_back(std::make_shared<std::thread>(&ThreadPool::threadManager, i));
      i++;
    }
}

void		FourCheese::ThreadPool::endThread(FourCheese::ThreadData &data)
{
  std::lock_guard<std::mutex>	lock(data._mutex);

  data._task = ThreadTask::END;
  data._condVar.notify_one();
}

FourCheese::ThreadPool::~ThreadPool()
{
  for (auto &ref : _vecData)
    endThread(ref);
  for (auto &ref : _vecThread)
    //ref.get()->detach();
  ref.get()->join();
}

void		FourCheese::ThreadPool::threadManager(int id)
{
  std::unique_lock<std::mutex>	lock(_vecData[id]._mutex);

  _vecData[id]._id = id;
  while (_vecData[id]._task != ThreadTask::END)
    {
      _vecData[id]._condVar.wait(lock, [&id]{
	  if (_vecData[id]._task != ThreadTask::FREE)
	    return (true);
	  return (false);
	});
      if (_vecData[id]._task == ThreadTask::BUSY)
	{
	  std::cout << "Encore du travaille id : " << _vecData[id]._id<< std::endl;
	  _vecData[id]._task = ThreadTask::FREE;
	}
      else
	std::cout << "Go dodo id : " << _vecData[id]._id<< std::endl;
    }
}

bool		FourCheese::ThreadPool::launchTask(std::string const & task)
{
  for (auto &ref : _vecData)
    {
      if (ref._mutex.try_lock() == true)
	{
	  std::cout << "Mutex lock !" << std::endl;
	  if (ref._task == ThreadTask::FREE)
	    {
	      ref._task = ThreadTask::BUSY;
	      ref._condVar.notify_one();
	    }
	  ref._mutex.unlock();
	}
      else
	std::cout << "Mutex alredy lock ? ? !" << std::endl;
    }
  return (true);
}
