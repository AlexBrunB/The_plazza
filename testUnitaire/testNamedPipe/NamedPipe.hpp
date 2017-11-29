//
// NamedPipe.hpp for NamedPipe in /home/deicide/CPP/cpp_plazza/include
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 13:14:48 2017 dEIcIdE
// Last update Tue Apr 18 00:00:25 2017 dEIcIdE
//

#ifndef		__NAMEDPIPE__
# define	__NAMEDPIPE__

# include <string>
# include <fstream>

# define	RW_ALL	0666

class	NamedPipe
{

private:

  enum fdType {IN = 0, OUT = 1};

  std::string			_name[2];
  int				_fdIn;
  int				_fdOut;
  bool				_creator;

  NamedPipe();
  
public:

  NamedPipe(std::string const & name, bool creat) throw();
  virtual ~NamedPipe();

  bool				sendMsg(std::string const & msgSend);
  std::string const &		receivMsg(std::string &msgReceived);
  
  bool				operator<<(std::string const & msgSend);
  std::string const &		operator>>(std::string & msgReceived);

};

#endif	//	__NAMEDPIPE__
