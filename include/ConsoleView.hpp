//
// View.hpp for View in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Tue Apr 25 16:02:07 2017 dEIcIdE
// Last update Wed Apr 26 13:18:28 2017 dEIcIdE
//

#ifndef		__CONSOLEVIEW__
# define	__CONSOLEVIEW__

# include <string>

namespace	FourCheese
{

  class	ConsoleView
  {

  private:

    public:

    ConsoleView();
    virtual ~ConsoleView();

    bool	getCommand(std::string & task);
    bool	printResult(std::string const & result);

  };

}

#endif	//	__CONSOLEVIEW__
