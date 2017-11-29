//
// ThreadPool.hpp for ThreadPool in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Thu Apr 20 11:19:36 2017 dEIcIdE
// Last update Sun Apr 23 00:34:45 2017 dEIcIdE
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
  enum class			ThreadTask : uint16_t
  {
    END				= 0,
    FREE			= 1,
    BUSY			= 2
  };

  typedef struct					ThreadData
  {
    unsigned int					_id;
    std::mutex						_mutex;
    std::condition_variable				_condVar;
    std::queue<std::function<void(std::string)>>	_taskFunction;
    std::queue<std::string>				_return;
    ThreadTask						_task;
    ThreadData();
    ThreadData(FourCheese::ThreadData &&other);
    ThreadData &operator=(FourCheese::ThreadData &&other);
  }							ThreadData;

  class	ThreadPool
  {

  private:

    unsigned int				_nbThread;
    std::vector<std::shared_ptr<std::thread>>	_vecThread;
    static std::vector<ThreadData>		_vecData;

    void		endThread(FourCheese::ThreadData &data);
    static void		threadManager(int i);

  public:

    ThreadPool(unsigned int nbThread);
    virtual ~ThreadPool();

    bool		launchTask(std::string const & task);

  };

}

#endif //	__THREADPOOL__
