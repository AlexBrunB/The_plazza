//
// Controler.cpp for Controler in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 23 16:15:37 2017 dEIcIdE
// Last update Sat Apr 29 16:48:18 2017 dEIcIdE
//

#include <exception>
#include <iostream>
#include <string>
#include <dirent.h>
#include <thread>
#include <mutex>
#include <queue>
#include <map>

#include <unistd.h>

#include "Controler.hpp"
#include "NamedPipe.hpp"
#include "Parser.hpp"
#include "Order.hpp"

FourCheese::Controler::Controler(unsigned int nbThread) :
  _nbThread(nbThread), _mutex(), _view(), _taskQue(), _resultQue(), _process(nbThread), _processData(), _runing(true)
{
#ifdef		__HISTO__
  DIR		*directory;
  struct dirent	*structDir;

  if ((directory = opendir("./historic")) != NULL)
    {
      while ((structDir = readdir(directory)) != NULL)
	if (std::string(structDir->d_name) != "." && std::string(structDir->d_name) != "..")
	  addHistoric(std::string("./historic/") + structDir->d_name);
      closedir(directory);
    }
#endif //	__HISTO__
}

bool				FourCheese::Controler::end(FourCheese::End action)
{
  std::lock_guard<std::mutex>	lock(_mutex);

  if (action == End::CHECK)
    {
      if (_runing == true)
	return (false);
      return (true);
    }
  _runing = false;
  return (true);
}

FourCheese::Controler::~Controler()
{
  end(End::TRUE);
  for (auto it = _processData.begin(); it != _processData.end(); )
    {
      _process.sendMsgTo("ENDCOM\n", it->first);
      _process.endProcess(it->first);
      it = _processData.erase(it);
    }
  _view.join();
}

int			FourCheese::Controler::addProcess()
{
  int			id = _process.launchProcess();
  _processData[id] = 0;
  return (id);
}

std::string const			FourCheese::Controler::getName(std::string const & name)
{
  int			i = name.size() - 1;
  unsigned int		length = 0;

  while (name[i] != '/' && i >= 0)
    {
      length++;
      i--;
    }
  return (name.substr(i + 1, length));
}

void				FourCheese::Controler::cleanHisto()
{
  for (auto it = _historic.begin() ; it != _historic.end() ;)
    it = _historic.erase(it);
}

bool				FourCheese::Controler::checkComand(std::string const &cmdLine)
{
  std::lock_guard<std::mutex>	lock(_mutex);
  auto				ithisto = _historic.end();

  if (cmdLine == "quit" || cmdLine == "Quit")
    return (false);
  if (cmdLine == "CLEAN_HISTO" || cmdLine == "CLEAN_HISTORIC")
    {
      cleanHisto();
      return (true);
    }
  _parser.parse_cmd_line(cmdLine);
  auto vecCmd = _parser.getListFile();
  for (auto &ref : vecCmd)
    {
      if (ref.second == FourCheese::Information::ERROR)
	std::cerr << ref.first << std::endl;
      else
	{
	  if ((ithisto = _historic.find(make_pair(getName(ref.first), ref.second))) != _historic.end())
	    _resultQue.push(ithisto->second);
	  else
	    _taskQue.push(std::to_string(ref.second) + ref.first + '\n');
	}
    }
  return (true);
}

void				FourCheese::Controler::execView()
{
  FourCheese::ConsoleView	consoleview;
  std::string			buff;

  while (!end(End::CHECK) && consoleview.getCommand(buff) && checkComand(buff))
    buff = "";
  end(End::TRUE);
}

void			FourCheese::Controler::launchView()
{
  _view = std::thread(&Controler::execView, this);
}

int				FourCheese::Controler::sendTask()
{
  int				id = 0;
  unsigned int			maxTask = _nbThread * 2;
  unsigned int			lastMin = maxTask + 1;
  std::unique_lock<std::mutex>	lock(_mutex, std::defer_lock);

  for (auto &ref : _processData)
    {
      if (ref.second < lastMin && ref.second < maxTask)
	{
	  lastMin = ref.second;
	  id = ref.first;
	}
    }
  if (id == 0)
    {
      if ((id = addProcess()) == -1)
	return (-1);
    }
  lock.lock();
  _processData[id] = _processData[id] + 1;
  _process.sendMsgTo(_taskQue.front(), id);
  _taskQue.pop();
  return (id);
}

void				FourCheese::Controler::addHistoric(std::string const & result)
{
  std::string::size_type	pos;

  try
    {
      if ((pos = result.rfind("_PHONE_NUMBER.histo")) != std::string::npos)
	_historic[make_pair(result.substr(11, pos - 11), FourCheese::PHONE_NUMBER)] = result;
      else if ((pos = result.rfind("_EMAIL_ADDRESS.histo")) != std::string::npos)
	_historic[make_pair(result.substr(11, pos - 11), FourCheese::EMAIL_ADDRESS)] = result;
      if ((pos = result.rfind("_IP_ADDRESS.histo")) != std::string::npos)
	_historic[make_pair(result.substr(11, pos - 11), FourCheese::IP_ADDRESS)] = result;
    }
  catch (std::out_of_range _error)
    {
      std::cerr << _error.what() << std::endl;
    }
}

int				FourCheese::Controler::getResult()
{
  std::unique_lock<std::mutex>	lock(_mutex, std::defer_lock);
  std::ifstream			result;
  std::string			receive;
  std::string			tmp;
  int				nbReceive = 0;

  for (auto it = _processData.begin() ; it != _processData.end() ;)
    {
      _process.receivMsgFrom(receive, it->first);
      if (receive.compare("ENDCOM") == 0)
	{
	  _process.endProcess(it->first);
	  it = _processData.erase(it);
	}
      else if (receive.compare("") != 0)
	{
	  it->second--;
	  result.open(receive);
	  if (result)
	    {
#ifdef		__HISTO__
	      addHistoric(receive);
#endif	//	__HISTO__
	      receive = "";
	      while (getline(result, tmp))
		receive += tmp + "\n";
	      result.close();
	      std::cout << receive;
	    }
	  nbReceive++;
	  it++;
	}
      else
	it++;
    }
  lock.lock();
  while (!_resultQue.empty())
    {
      tmp = _resultQue.front();
      if (tmp == "")
	std::cerr << "ERROR 404 : File not found" << std::endl;
      result.open(tmp);
      _resultQue.pop();
      if (result)
	{
	  receive = "";
	  while (getline(result, tmp))
	    receive += tmp + "\n";
	  result.close();
	  nbReceive++;
	  std::cout << receive;
	}
    }
  lock.unlock();
  return (nbReceive);
}

bool				FourCheese::Controler::taskRemins()
{
  std::lock_guard<std::mutex>	lock(_mutex);

  return (_taskQue.empty() ? false : true);
}

int				FourCheese::Controler::launch()
{
  bool				clean = false;

  launchView();
  while (!end(End::CHECK) || taskRemins())
    {
      while (taskRemins())
	sendTask();
      getResult();
      usleep(5);
    }
  while (!clean)
    {
      clean = true;
      for (auto &ref : _processData)
	{
	  if (ref.second != 0)
	    clean = false;
	}
      getResult();
    }
  return (0);
}
