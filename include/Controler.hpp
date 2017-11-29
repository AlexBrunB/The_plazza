//
// Controler.hpp for Controler in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 23 15:45:10 2017 dEIcIdE
// Last update Fri Apr 28 15:50:58 2017 dEIcIdE
//

#ifndef		__CONTROLER__
# define	__CONTROLER__

# include <utility>
# include <string>
# include <thread>
# include <mutex>
# include <queue>
# include <map>

# include "NamedPipe.hpp"
# include "ConsoleView.hpp"
# include "Process.hpp"
# include "Parser.hpp"

namespace	FourCheese
{

  enum class	End : bool
  {
    TRUE	= true,
    CHECK	= false
  };
  
  class	Controler
  {

  private:

    unsigned int				_nbThread;
    std::mutex					_mutex;
    std::thread					_view;
    std::queue<std::string>			_taskQue;
    std::queue<std::string>			_resultQue;
    FourCheese::Process				_process;
    std::map<unsigned int, unsigned int>	_processData;
    FourCheese::Parser				_parser;
    std::map<std::pair<std::string, FourCheese::Information>, std::string>	_historic;
    bool					_runing;

    void		cleanHisto();
    std::string const	getName(std::string const & name);
    int			addProcess();
    void		launchView();
    void		execView();
    bool		checkComand(std::string const & cmdLine);
    void		addHistoric(std::string const & result);
    int			sendTask();
    int			getResult();
    bool		end(FourCheese::End action);
    bool		taskRemins();

  public:

    Controler(unsigned int nbThread);
    virtual ~Controler();
    
    int			launch();

  };

}

#endif //	__CONTROLER__
