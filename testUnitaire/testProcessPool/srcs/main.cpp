//
// main.cpp for main in /home/deicide/CPP/cpp_plazza/srcs
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Sun Apr 16 13:08:50 2017 dEIcIdE
// Last update Wed Apr 26 10:43:38 2017 dEIcIdE
//

#include <string>
#include <iostream>
#include <unistd.h>

#include "NamedPipe.hpp"
#include "Process.hpp"

int		main(int ac, char **av)
{
  FourCheese::Process	lol;
  std::string		tmp;

  lol.launchProcess();
  std::cout << (*(lol._com[lol._id + 1]) >> tmp) << std::endl;
  *(lol._com[lol._id + 1]) << "Job done\n";
  *(lol._com[lol._id + 1]) >> tmp;
  sleep(2);
  while (tmp.compare("Done") != 0)
    *(lol._com[lol._id + 1]) >> tmp;
  std::cout << tmp  << " father done "<< std::endl;
  return (0);
}

