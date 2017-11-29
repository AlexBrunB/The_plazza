//
// Parser.hpp for plazza in /home/vico/CPP/cpp_plazza
// 
// Made by vico
// Login   <victor1.pancrate@epitech.eu>
// 
// Started on  Sat Apr 22 12:52:23 2017 vico
// Last update Wed Apr 26 16:43:16 2017 vico
//

#ifndef PARSER_HPP_
# define PARSER_HPP_

#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <string>
#include "Order.hpp"
namespace	FourCheese
{
  class		Parser
  {
    std::map<FourCheese::Information, std::regex>				my_regex;
    std::vector<std::pair<std::string, FourCheese::Information> >		my_files;
    bool								cmd_check(const std::string &line);
  public:
    Parser();
    ~Parser();
    const std::string							parse_file(const std::string &file_name, FourCheese::Information order);
    bool								parse_cmd_line(const std::string &cmd_line);
    const std::vector<std::pair<std::string, FourCheese::Information> >	&getListFile() const;
  };
}
#endif
