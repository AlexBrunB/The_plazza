//
// main.cpp for main in /home/deicide/CPP/cpp_plazza/srcs
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 13:08:50 2017 dEIcIdE
// Last update Sat Apr 29 23:50:45 2017 dEIcIdE
//

#include <string>
#include <iostream>
#include <exception>

#include "NamedPipe.hpp"
#include "Controler.hpp"

int			main(int ac, char **av)
{
  int			i;

  if (ac > 1)
    {
      try
	{
	  i = std::stoi(av[1]);
      	}
      catch (std::out_of_range _error)
	{
	  std::cerr << _error.what() << std::endl;
	  return (1);
	}
      catch (std::invalid_argument _error)
	{
	  std::cerr << _error.what() << std::endl;
	  return (1);
	}
      if (i > 10000)
	i = 10000;
      if (i < 1)
	i = 1;
      FourCheese::Controler	controler(i);
      controler.launch();
    }
  else
    std::cerr << "./Plazza [nbThread]" << std::endl;
  return (0);
}

