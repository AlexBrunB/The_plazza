//
// PlazzaError.hpp for PlazzaError in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 15:08:47 2017 dEIcIdE
// Last update Sun Apr 16 17:51:10 2017 dEIcIdE
//

#ifndef		__PLAZZAERROR__
# define	__PLAZZAERROR__

# include <exception>
# include <string>

class	PlazzaError	: public std::exception
{

protected:

  std::string		_errorMsg;

public:

  PlazzaError(std::string const & errorMsg = "Unknown Error") throw();
  virtual ~PlazzaError() throw();

  virtual const char	*what() const throw();

};

class	NamedPipeError	: public PlazzaError
{

private:

  int			_stage;

public:

  NamedPipeError(std::string const & errorMsg = "NamedPipe Unknown Error", int stage = 1) throw();
  virtual ~NamedPipeError() throw();

  int			getStage() const;

};

class	PlazzaCriticalError	: public PlazzaError
{

public:

  PlazzaCriticalError(std::string const & errorMsg = "Unknown Critical Error") throw();
  virtual ~PlazzaCriticalError() throw();

};

#endif	//	__PLAZZAERROR__
