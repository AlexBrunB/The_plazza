##
## Makefile for Makefile in /home/deicide/CPP/cpp_plazza
## 
## Made by dEIcIdE
## Login   <deicide@epitech.net>
## 
## Started on  Sun Apr 16 13:18:40 2017 dEIcIdE
## Last update Wed Apr 19 18:11:52 2017 dEIcIdE
##

CC	=	g++

RM	=	rm -f

NAME	=	plazza

SRCS_FILE =	./srcs/

SRCS	 = 	$(SRCS_FILE)main.cpp		\
		$(SRCS_FILE)PlazzaError.cpp	\
		$(SRCS_FILE)NamedPipe.cpp	\
		$(SRCS_FILE)get_next_line.cpp	\
		$(SRCS_FILE)Process.cpp

CPPFLAGS =	-Wall -Wextra -std=c++14 -g
CPPFLAGS +=	-I./include

OBJS	=	$(SRCS:.cpp=.o)

all:		$(NAME) 

$(NAME):	$(OBJS)
		$(CC)  $(CPPFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all re clean fclean
