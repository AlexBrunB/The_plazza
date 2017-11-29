//
// Process.hpp for Process in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Tue Apr 18 16:19:05 2017 dEIcIdE
// Last update Fri Apr 28 15:20:18 2017 dEIcIdE
//

#ifndef		__PROCESS__
# define	__PROCESS__

# include <map>
# include <memory>

# include "NamedPipe.hpp"

namespace	FourCheese
{

  class	Process
  {

  private:

    unsigned int							_id;
    unsigned int							_nbThread;
    std::map<unsigned int, std::unique_ptr<FourCheese::NamedPipe>>	_com;

    bool			checkTime(int task);

  public:

    Process(unsigned int nbThread);
    virtual ~Process();

    int				launchProcess();
    bool			endProcess(unsigned int idTarget);
    void			clean();
    void			soonAction();
    bool			sendMsgTo(std::string const & msgSend, unsigned int idTarget);
    std::string const &		receivMsgFrom(std::string & msg, unsigned int idTarget);

  };

}

#endif	//	__PROCESS__
