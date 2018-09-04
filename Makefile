# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/25 09:04:20 by tle-huu-          #+#    #+#              #
#    Updated: 2018/09/03 16:27:39 by tle-huu-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = n_puzzle

INCLUDES += /nfs/2017/t/tle-huu-/.brew/Cellar/boost/1.67.0_1/include/ \
			$(shell pkg-config --cflags sfml-window sfml-graphics sfml-system)

SRCS =  srcs/Parser.cpp			\
	srcs/Puzzle.cpp				\
	srcs/Ai.cpp					\
	srcs/Drawer.cpp				\
	srcs/main.cpp

OBJS = $(SRCS:.cpp=.o)

CXX = clang++
CXXFLAGS += -std=c++14
# CXXFLAGS += -Wall -Wextra -Werror

LDFLAGS += $(shell pkg-config --libs sfml-window sfml-graphics sfml-system)
LDFLAGS +=  -fsanitize=address


RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean all
