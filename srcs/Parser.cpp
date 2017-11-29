//
// parsing_function.cpp for plazza in /home/vico/CPP/cpp_plazza/srcs
// 
// Made by vico
// Login   <victor1.pancrate@epitech.eu>
// 
// Started on  Thu Apr 20 11:42:26 2017 vico
// Last update Fri Apr 28 17:09:21 2017 dEIcIdE
//

#include "Parser.hpp"

FourCheese::Parser::Parser()
{
  my_regex[FourCheese::PHONE_NUMBER] = std::regex("[0-9]\\s?[0-9]\\s?[0-9]\\s?[0-9]\\s?[0-9]\\s?[0-9]\\s?[0-9]\\s?[0-9]\\s?[0-9]\\s?[0-9]"); //regex telephone
  my_regex[FourCheese::IP_ADDRESS] = std::regex("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}"); //regex adresse ip
  my_regex[FourCheese::EMAIL_ADDRESS] = std::regex("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+"); //regex email
}

FourCheese::Parser::~Parser()
{
}

bool		check_valid_num(const std::string &num)
{
  int		value;
  bool		check;
  unsigned int	i;

  i = 0;
  if (num.size() > 1)
    {
      check = false;
      while (i < num.size())
	{
	  if (num[i] >= '1' && num[i] <= '9' && check == false)
	    check = true;
	  if (num[i] == '0' && check == false)
	    return (false);
	  i++;
	}
    }
  std::istringstream(num) >> value;
  if (value >= 256)
    return (false);
  return (true);
}

bool		is_valid_ipadress(const std::string &ip)
{
  unsigned int	i;
  unsigned int	tmp;

  i = 0;
  tmp = 0;
  while (ip[i] != '.')
    i++;
  if (!check_valid_num(ip.substr(tmp, i - tmp)))
    return (false);
  i++;
  tmp = i;
  while (ip[i] != '.')
    i++;
  if (!check_valid_num(ip.substr(tmp, i - tmp)))
    return (false);
  i++;
  tmp = i;
  while (ip[i] != '.')
    i++;
  if (!check_valid_num(ip.substr(tmp, i - tmp)))
    return (false);
  i++;
  tmp = i;
  while (i < ip.size())
    i++;
  if (!check_valid_num(ip.substr(tmp, i - tmp)))
    return (false);
  return (true);
}

void		getNameFile(const std::string &file_path, std::string &out_name)
{
  int		i;
  unsigned int	length;

  i = file_path.size() - 1;
  length = 0;
  while (file_path[i] != '/' && i >= 0)
    {
      length++;
      i--;
    }
  out_name = "./historic/" + file_path.substr(i + 1, length);
}

const std::string	FourCheese::Parser::parse_file(const std::string &file_name, FourCheese::Information type)
{
  unsigned int	i;
  int		tmp;
  std::smatch	match;
  std::string	line;
  std::string	file;
  std::string	output_name;
  char		charac;
  std::ifstream	input(file_name);
  std::ofstream output;

  if (input.is_open())
    {
      getNameFile(file_name, output_name);
      if (type == FourCheese::Information::IP_ADDRESS)
	output_name += "_IP_ADDRESS.histo";
      else if (type == FourCheese::Information::EMAIL_ADDRESS)
	output_name += "_EMAIL_ADDRESS.histo";
      else
	output_name += "_PHONE_NUMBER.histo";
      output.open(output_name, std::ofstream::out);
      while (input.get(charac))
	file += charac;
      i = 0;
      while (i < file.size())
	{
	  tmp = i;
	  while (file[i] != '\n' && i < file.size())
	    i++;
	  line = file.substr(tmp, i - tmp + 1);
	  while (std::regex_search(line, match, this->my_regex[type]))
	    {
	      for (auto &it : match)
		{
		  if (type == FourCheese::IP_ADDRESS)
		    {
		      if (is_valid_ipadress(it))
			output << it << std::endl;
		    }
		  else
		    output << it << std::endl;
		}
	      line = match.suffix().str();
	    }
	  i++;
	}
      input.close();
      output.close();
      return (output_name);
    }
  return ("");
}

bool		FourCheese::Parser::cmd_check(const std::string &line)
{
  std::string			order;
  unsigned int			deb_nfile;
  unsigned int			length;
  unsigned int			i;
  std::vector<std::string>	list_file;

  i = 0;
  while (i < line.size() && (line[i] < 33 || line[i] == 127))
    i++;
  if (i == line.size())
    {
      this->my_files.push_back(std::make_pair("Error command : " + line, FourCheese::Information::ERROR));
      return (false);
    }
  while (i < line.size())
    {
      deb_nfile = i;
      while (i < line.size() && (line[i] >= 33 && line[i] < 127))
	i++;
      length = i - deb_nfile;
      while (i < line.size() && (line[i] < 33 || line[i] == 127))
	i++;
      if (i == line.size())
	{
	  order = line.substr(deb_nfile, length);
	  if (order != "EMAIL_ADDRESS" && order != "IP_ADDRESS" && order != "PHONE_NUMBER")
	    {
	      this->my_files.push_back(std::make_pair("Error command : " + line, FourCheese::Information::ERROR));
	      return (false);
	    }
	}
      else
	list_file.push_back(line.substr(deb_nfile, length));
    }
  if (list_file.size() == 0)
    {
      this->my_files.push_back(std::make_pair("Error command : " + line, FourCheese::Information::ERROR));
      return (false);
    }
  for (auto &it : list_file)
    {
      if (order == "EMAIL_ADDRESS")
	this->my_files.push_back(std::make_pair(it, FourCheese::Information::EMAIL_ADDRESS));
      else if (order == "IP_ADDRESS")
	this->my_files.push_back(std::make_pair(it, FourCheese::Information::IP_ADDRESS));
      else
	this->my_files.push_back(std::make_pair(it, FourCheese::Information::PHONE_NUMBER));
    }
  return (true);
}

bool		FourCheese::Parser::parse_cmd_line(const std::string &cmd_line)
{
  unsigned int	tmp;
  unsigned int	i;

  if (this->my_files.size() > 0)
    this->my_files.clear();
  tmp = 0;
  i = 0;
  while (i < cmd_line.size())
    {
      if (cmd_line[i] == ';')
	{
	  cmd_check(cmd_line.substr(tmp, i - tmp));
	  tmp = i + 1;
 	}
      i++;
    }
  if (tmp < cmd_line.size())
    cmd_check(cmd_line.substr(tmp, i - tmp));
  return (true);
}

const std::vector<std::pair<std::string, FourCheese::Information> >	&FourCheese::Parser::getListFile() const
{
  return (this->my_files);
}
