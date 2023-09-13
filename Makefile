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

NAME = webserv

SRC_DIR	 = ./sources
BLD_DIR	 = ./build
TMP_DIR	 = ./tmp
HDR_DIR	 = ./headers $(SRC_DIR)/classes

SRC	 = $(wildcard $(SRC_DIR)/*.cpp)
OBJ	 = $(patsubst $(SRC_DIR)/%.cpp,$(BLD_DIR)/%.o,$(SRC))
DEP	 = $(OBJ:.o=.d)
HDR	 = $(addprefix -I, $(HDR_DIR))

CXX		 = c++
DEL		 = rm -rf
MKDIR	 = mkdir -p

CXXFLAGS	 = -Wall -Wextra -Werror -std=c++98
DEPFLAGS	 = -MMD -MF

all: $(NAME)

$(NAME): $(OBJ) | $(TMP_DIR)
	$(CXX) $(CXXFLAGS) $(HDR) $(OBJ) -o $(NAME)

clean:
	$(DEL) $(DEP) $(OBJ) $(BLD_DIR) $(TMP_DIR)

fclean: clean
	$(DEL) $(NAME)

re: fclean all

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) $(HDR) -c $< -o $@ $(DEPFLAGS) $(@:.o=.d)

$(BLD_DIR):
	$(MKDIR) $(BLD_DIR)

$(TMP_DIR):
	$(MKDIR) $(TMP_DIR)

-include $(DEP)

.PHONY: all clean fclean re
