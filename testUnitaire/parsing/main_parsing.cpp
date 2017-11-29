//
// main_parsing.cpp for plazza in /home/vico/CPP/cpp_plazza/srcs
// 
// Made by vico
// Login   <victor1.pancrate@epitech.eu>
// 
// Started on  Thu Apr 20 12:05:39 2017 vico
// Last update Wed Apr 26 18:35:22 2017 vico
//

#include <string>
#include <iostream>
#include <fstream>
#include "Parser.hpp"

void	choose_type_parsing(const std::string &, FourCheese::Information);

int	main(int ac, char **av)
{
  FourCheese::Parser	parser;
  //std::string		input;
  //std::ifstream		file(av[1]);
  
  for (int i = 1; i < ac; i++)
    {
      //std::ifstream		file(av[i]);
      //while (file.get(charac))
      //input += charac;
      parser.parse_cmd_line(av[i]);
      auto tmp = parser.getListFile();
      for (auto &it : tmp)
	{
	  if (it.second == 0)
	    std::cout << it.first << "   PHONE_NUMBER" << std::endl;
	  else if (it.second == 1)
	    std::cout << it.first << "   EMAIL_ADDRESS" << std::endl;
	  else if (it.second == 2)
	    std::cout << it.first << "   IP_ADDRESS" << std::endl;
	  else
	    std::cout << it.first << "   ERROR" << std::endl;
	}
    }
  //(void)ac;
  //parser.parse_file(av[1], FourCheese::PHONE_NUMBER);
  //parser.parse_file(av[1], FourCheese::IP_ADDRESS);
  //parser.parse_file(av[1], FourCheese::EMAIL_ADDRESS);
}
