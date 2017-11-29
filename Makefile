##
## Makefile for Makefile in /home/deicide/CPP/cpp_plazza
## 
## Made by dEIcIdE
## Login   <deicide@epitech.net>
## 
## Started on  Sun Apr 16 13:18:40 2017 dEIcIdE
## Last update Sat Apr 29 13:35:34 2017 dEIcIdE
##

CC		=	g++

RM		=	rm -f

NAME		=	plazza

FIFO		=	fifo

HISTORIC	=	historic

SRCS_FILE	=	./srcs/

SRCS		= 	$(SRCS_FILE)main.cpp		\
			$(SRCS_FILE)PlazzaError.cpp	\
			$(SRCS_FILE)NamedPipe.cpp	\
			$(SRCS_FILE)get_next_line.cpp	\
			$(SRCS_FILE)Process.cpp		\
			$(SRCS_FILE)ThreadPool.cpp	\
			$(SRCS_FILE)Controler.cpp	\
			$(SRCS_FILE)ConsoleView.cpp	\
			$(SRCS_FILE)Parser.cpp

CPPFLAGS	=	-Wall -Wextra -std=c++14
CPPFLAGS	+=	-I./include -lpthread

ifeq			($(HISTO), 1)
CPPFLAGS	+=	-D __HISTO__
endif

OBJS		=	$(SRCS:.cpp=.o)

all:		$(NAME) $(FIFO) $(HISTORIC)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)

$(FIFO):
		mkdir $(FIFO)

$(HISTORIC):
		mkdir $(HISTORIC)

cleanhisto:
		$(RM) $(HISTORIC)/*

cleanfifo:
		$(RM) $(FIFO)/*

clean:		cleanhisto cleanfifo
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all re cleanhisto cleanfifo clean fclean
