/*
** get_next_line.c for get_next_line in /home/deicide/CPE/CPE_2016_getnextline
** 
** Made by Adrien Marois
** Login   <deicide@epitech.net>
** 
** Started on  Tue Nov 22 08:52:24 2016 Adrien Marois
** Last update Mon Apr 17 17:54:35 2017 dEIcIdE
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

static int	get_line_length(char *str, int y)
{
  int		i;

  i = 0;
  while ((i != y) && (str[i] != '\n'))
    i++;
  return (i);
}

static char	*add_line(char *line,
			  char *buff, int buff_length, int y)
{
  static int	length = 0;
  char		*tmp;
  int		i;

  if (line == 0)
    length = 0;
  if ((tmp = (char *)malloc(sizeof(char) * (length + buff_length + 1))) == 0)
    return (0);
  i = 0;
  while (i < length)
    {
      tmp[i] = line[i];
      i++;
    }
  while (y < buff_length)
    {
      tmp[i + y] = buff[y];
      y++;
    }
  tmp[i + y] = '\0';
  length = i + y;
  if (line != 0)
    free(line);
  return (tmp);
}

static char	*return_line(char *line, char *buff, int *y, int *i)
{
  long		hi;

  if (*i == 0)
    {
      *i = get_line_length(buff, *y) + 1;
      if (*i == *y)
	{
	  *i = 0;
	  return (add_line(line, buff, (*y) - 1, 0));
	}
      return (add_line(line, buff, (*i) - 1, 0));
    }
  hi = *i;
  *i = (*i) + get_line_length(&buff[*i], (*y) - (*i)) + 1;
  if (*i == *y)
    {
      *i = 0;
      return (add_line(line, &buff[hi], (*y) - hi - 1, 0));
    }
  return (add_line(line, &buff[hi], (*i) - hi - 1, 0));
}

char		*get_next_line(const int fd)
{
  static char	buff[READ_SIZE + 1];
  static int	i = 0;
  static int	y = 0;
  char		*line;

  line = 0;
  if (i != 0)
    {
      if (buff[i + get_line_length(&buff[i], y - i)] != '\n')
	line = add_line(line, &buff[i], y - i, 0);
      else
	return (return_line(line, buff, &y, &i));
    }
  i = 0;
  while ((y = read(fd, buff, READ_SIZE)) != 0)
    {
      if (y < 0)
	return (0);
      buff[y] = '\0';
      if (buff[get_line_length(buff, y)] != '\n')
	line = add_line(line, buff, y, 0);
      else
	return (return_line(line, buff, &y, &i));
    }
  return (line);
}
