//
// main.cpp for main in /home/deicide/CPP/cpp_plazza/srcs
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 13:08:50 2017 dEIcIdE
// Last update Tue Apr 18 16:37:48 2017 dEIcIdE
//

#include <string>
#include <iostream>
#include <unistd.h>

#include "NamedPipe.hpp"


int		main(int ac, char **av)
{
  NamedPipe	creatPipe("./theGreatPipe", false);
  int		i = 0;
  std::string	msg;
  

  while (i < 20)
    {
      sleep(1);
      std::cout << "Le mesage est : " << (creatPipe >> msg) << std::endl;
      i++;
    }
  return (0);
  }



int		main(int ac, char **av)
{
  NamedPipe	creatPipe("./theGreatPipe", true);
  int		i = 0;

  while (i < 20)
    {
      if (i == 10)
	creatPipe << "Jolie jolie\n";
      else if (i % 2 == 0)
	creatPipe << "Luck je suis ton Pipe\n";
      else
	creatPipe << "Heu je sais pas tros\n";
      i++;
    }
  return (0);
}

