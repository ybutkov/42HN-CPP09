NAME		= btc

SRC 		= src
BUILD_DIR 	= build

INCLUDES 	= -Iincludes
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -g -std=c++17 $(INCLUDES) 

SRCS_FILES 	= main.cpp \
				BitcoinExchange.cpp \
				CSVReader.cpp

CPP_FILES  	= $(addprefix $(SRC)/, $(SRCS_FILES))
OBJS		= $(CPP_FILES:%.cpp=$(BUILD_DIR)/%.o)
BUILD_DIRS := $(sort $(dir $(OBJS)))

all: $(NAME)

$(NAME): $(BUILD_DIRS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIRS):
	@mkdir -p $@

$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean f: clean
	rm -f $(NAME)

re: fclean all

v: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	  	--error-exitcode=1 ./$(NAME)

.PHONY: all clean fclean re
