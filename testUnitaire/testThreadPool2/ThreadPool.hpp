//
// ThreadPool.hpp for ThreadPool in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Thu Apr 20 11:19:36 2017 dEIcIdE
// Last update Mon Apr 24 17:14:48 2017 dEIcIdE
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

namespace	FourCheese
{

  class	ThreadPool
  {

  private:

    unsigned int					_nbThread;
    std::mutex						_mutex;
    std::condition_variable				_condVar;
    std::vector<std::shared_ptr<std::thread>>		_vecThread;
    std::queue<std::string>				_return;
    std::queue<std::function<std::string()>>	_taskFunction;
    bool						_end;

    void		endThread();
    void		threadManager(int id);

  public:

    ThreadPool(unsigned int nbThread);
    virtual ~ThreadPool();

    bool		launchTask(std::string const & task);
    bool		getResult(std::string &result);

  };

}

#endif //	__THREADPOOL__
