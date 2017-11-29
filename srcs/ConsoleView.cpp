//
// ConsoleView.cpp for ConsoleView in /home/deicide/CPP/cpp_plazza
// 
// Made by dEIcIdE
// Login   <deicide@epitech.net>
// 
// Started on  Wed Apr 26 09:54:39 2017 dEIcIdE
// Last update Wed Apr 26 23:46:27 2017 dEIcIdE
//

#include <iostream>
#include <string>

#include "ConsoleView.hpp"

FourCheese::ConsoleView::ConsoleView()
{
}

FourCheese::ConsoleView::~ConsoleView()
{
}

bool		FourCheese::ConsoleView::getCommand(std::string & task)
{
  getline(std::cin, task);
  if (!std::cin.eof())
    return (true);
  return(false);
}

bool	FourCheese::ConsoleView::printResult(std::string const & result)
{
  if (result == "")
    return (false);
  std::cout << result << std::endl;
  return (true);
}
