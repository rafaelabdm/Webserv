NAME		 = webserv
CONF_FILE	 = serv.conf

SRC_DIR = sources
BLD_DIR = build
HDR_DIR = headers $(SRC_DIR)/classes $(SRC_DIR)/templates

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BLD_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)
HDR = $(addprefix -I, $(HDR_DIR))

CXX = c++
DEL = rm -rf
MKDIR = mkdir -p

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3
DEPFLAGS = -MMD -MF
VALFLAGS = -q --show-leak-kinds=all --track-origins=yes

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(HDR) $(OBJ) -o $(NAME)

clean:
	$(DEL) $(BLD_DIR)

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
