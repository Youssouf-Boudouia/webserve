# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 12:46:16 by yboudoui          #+#    #+#              #
#    Updated: 2023/09/12 19:41:06 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	webserve

#-----------------------------------------------------------------------------#

SRCS				=	main.cpp\
						srcs/MessageTransporter.cpp \
						srcs/Queue.cpp \
						srcs/SocketBind.cpp \
						srcs/SocketConnection.cpp

LIBKQEUE			=	./dependencies/libkqueue/build

INCS				=	./incs \
						$(LIBKQEUE)/include

LIBS				=	$(LIBKQEUE)/lib/libkqueue.a

OBJS				=	$(SRCS:.cpp=.o)

#-----------------------------------------------------------------------------#

CXX					=	c++

CXXFLAGS			=	-Wall -Wextra -Werror -std=c++98

RM					=	rm -f


.cpp.o:
			$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCS)) -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCS)) $(OBJS) -o $(NAME) $(LIBS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean
			make all

.PHONY:		all clean fclean re
