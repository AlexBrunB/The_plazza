//
// ThreadPool.hpp for ThreadPool in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Thu Apr 20 11:19:36 2017 dEIcIdE
// Last update Thu Apr 27 01:07:51 2017 dEIcIdE
//

#ifndef		__THREADPOOL__
# define	__THREADPOOL__

# include <condition_variable>
# include <functional>
# include <string>
# include <thread>
# include <mutex>
# include <vector>
# include <queue>

# include "Parser.hpp"

namespace	FourCheese
{

  class	ThreadPool
  {

  private:

    FourCheese::Parser					_parser;
    unsigned int					_nbThread;
    std::mutex						_mutex;
    std::condition_variable				_condVar;
    std::vector<std::shared_ptr<std::thread>>		_vecThread;
    std::queue<std::string>				_return;
    std::queue<std::function<const std::string()>>	_taskFunction;
    bool						_end;

    void		endThread();
    void		threadManager();

  public:

    ThreadPool(unsigned int nbThread);
    virtual ~ThreadPool();

    bool		launchTask(std::string const & task);
    bool		getResult(std::string &result);

  };

}

#endif //	__THREADPOOL__
