//
// NamedPipe.hpp for NamedPipe in /home/deicide/CPP/cpp_plazza/include
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 13:14:48 2017 dEIcIdE
// Last update Sun Apr 23 15:55:41 2017 dEIcIdE
//

#ifndef		__NAMEDPIPE__
# define	__NAMEDPIPE__

# include <string>
# include <fstream>

# define	RW_ALL	0666

namespace	FourCheese
{
  
  class	NamedPipe
  {

  private:

    enum fdType {IN = 0, OUT = 1};

    std::string			_name[2];
    int				_fdIn;
    int				_fdOut;
    bool			_creator;

    NamedPipe();
  
  public:

    NamedPipe(std::string const & name, bool creat) throw();
    NamedPipe(std::string const & name) throw();
    NamedPipe(FourCheese::NamedPipe &&other);
    virtual ~NamedPipe();

    void				swapFd();
    bool				sendMsg(std::string const & msgSend) const;
    std::string const &			receivMsg(std::string &msgReceived) const;

    FourCheese::NamedPipe		&operator=(FourCheese::NamedPipe &&other);
    bool				operator<<(std::string const & msgSend) const;
    std::string const &			operator>>(std::string & msgReceived) const;

  };

}

#endif	//	__NAMEDPIPE__
