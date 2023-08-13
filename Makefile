# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/04 19:37:28 by rapdos-s          #+#    #+#              #
#    Updated: 2023/08/04 19:37:28 by rapdos-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 = webserv
CONF_FILE	 = examples/webserv.conf

SRC_DIR	 = ./sources
BLD_DIR	 = ./build
HDR_DIR	 = ./headers $(SRC_DIR)/classes $(SRC_DIR)/templates

SRC	 = $(wildcard $(SRC_DIR)/*.cpp)
OBJ	 = $(patsubst $(SRC_DIR)/%.cpp,$(BLD_DIR)/%.o,$(SRC))
DEP	 = $(OBJ:.o=.d)
HDR	 = $(addprefix -I, $(HDR_DIR))

CXX		 = c++
DEL		 = rm -rf
MKDIR	 = mkdir -p

DEBUG		 = false
CXXFLAGS	 = -Wall -Wextra -Werror -std=c++98 \
			   -g3 -DDEBUG=$(DEBUG) -fmax-errors=1
DEPFLAGS	 = -MMD -MF
VALFLAGS	 = --leak-check=full \
			   --show-leak-kinds=all \
			   --track-origins=yes \
			   --track-fds=yes \
			   --show-reachable=yes \
			   --error-limit=yes

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(HDR) $(OBJ) -o $(NAME)

clean:
	$(DEL) $(DEP) $(OBJ) $(BLD_DIR)

fclean: clean
	$(DEL) $(NAME)

re: fclean all

test: $(NAME)
	./$(NAME) $(CONF_FILE)

help: $(NAME)
	./$(NAME) --help

valgrind: $(NAME)
	valgrind $(VALFLAGS) ./$(NAME) $(CONF_FILE)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) $(HDR) -c $< -o $@ $(DEPFLAGS) $(@:.o=.d)

$(BLD_DIR):
	$(MKDIR) $(BLD_DIR)

-include $(DEP)

.PHONY: all clean fclean re test help valgrind
