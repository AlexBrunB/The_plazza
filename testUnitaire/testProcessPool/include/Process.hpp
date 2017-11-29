//
// Process.hpp for Process in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Tue Apr 18 16:19:05 2017 dEIcIdE
// Last update Wed Apr 19 18:05:48 2017 dEIcIdE
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

    

  public:

    unsigned int							_id;
    std::map<unsigned int, std::unique_ptr<FourCheese::NamedPipe>>	_com;

    Process();
    ~Process();

    bool	launchProcess();
    void	clean();
    void	soonAction();
  };

}

#endif	//	__PROCESS__
