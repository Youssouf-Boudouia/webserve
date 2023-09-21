# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 12:46:16 by yboudoui          #+#    #+#              #
#    Updated: 2023/09/21 17:28:49 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	webserve

#-----------------------------------------------------------------------------#

SRCS				=	main.cpp\
						srcs/MessageTransporter.cpp \
						srcs/Queue.cpp \
						srcs/SocketBind.cpp \
						srcs/SocketConnection.cpp \
						srcs/Request.cpp

PATH_PACKAGE		=	./dependencies/package
PATH_BUILD			=	./dependencies/build
PATH_LIB			=	./dependencies/lib

INCS				=	./incs \
						$(PATH_LIB)/libkqueue/include

LIBS				=	$(PATH_LIB)/libkqueue/lib/libkqueue.a

OBJS				=	$(SRCS:.cpp=.o)

#-----------------------------------------------------------------------------#

CXX					=	clang++

CXXFLAGS			=	-Wall -Wextra -Werror -std=c++98 -g3

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
			$(RM)r $(PATH_BUILD)
			$(RM)r $(PATH_LIB)

re:			fclean
			make all

install_libkqueue:
			if [ ! -d "$(PATH_LIB)/libkqueue" ]; then mkdir -p $(PATH_LIB)/libkqueue; fi
			if [ ! -d "$(PATH_BUILD)/libkqueue" ]; then mkdir -p $(PATH_BUILD)/libkqueue; fi
			cd $(PATH_BUILD)/libkqueue; \
			cmake -G "Unix Makefiles" \
				-DCMAKE_INSTALL_PREFIX=../../lib/libkqueue \
				-DCMAKE_INSTALL_LIBDIR=lib \
				../../package/libkqueue; \
			make install; 

install:
	make install_libkqueue

.PHONY:		all clean fclean re install
