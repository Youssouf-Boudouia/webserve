# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 12:46:16 by yboudoui          #+#    #+#              #
#    Updated: 2023/09/24 12:47:54 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	webserve

#-----------------------------------------------------------------------------#

SRCS				=	main.cpp\
						srcs/MessageTransporter.cpp \
						srcs/Queue.cpp \
						srcs/SocketBind.cpp \
						srcs/SocketConnection.cpp \
						srcs/Request.cpp\
						srcs/Response.cpp

PATH_PACKAGE		=	./dependencies/package
PATH_BUILD			=	./dependencies/build
PATH_LIB			=	./dependencies/lib

INCS				=	./incs \
						$(PATH_LIB)/libkqueue/include

LIBS				=	$(PATH_LIB)/libkqueue/lib/libkqueue.a

OBJS_DIR			=	./objs

OBJS				:=	$(SRCS:%.cpp=$(OBJS_DIR)/%.o)

DEPS				:=	$(OBJS:%.o=%.d)

#-----------------------------------------------------------------------------#

CXX					=	clang++

CXXFLAGS			=	-Wall -Wextra -Werror -MMD -std=c++98 -g3

RM					=	rm -f

$(OBJS_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCS)) -c $< -o $@

$(NAME):	$(OBJS)
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCS)) $(OBJS) -o $(NAME) $(LIBS)

all:		$(NAME)

clean:
	$(RM) -r $(OBJS_DIR)

fclean:		clean
	$(RM) $(NAME)
	$(RM) -r $(PATH_BUILD)
	$(RM) -r $(PATH_LIB)

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

-include $(DEPS)
