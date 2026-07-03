NAME		= PmergeMe

SRC 		= src
BUILD_DIR 	= build

INCLUDES 	= -Iincludes
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -O2 -std=c++17 $(INCLUDES) 

SRCS_FILES 	= main.cpp \
				PmergeMe.cpp \
				TimeProfiler.cpp


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
	  	--error-exitcode=1 ./$(NAME) $$(shuf -i 1-100000 -n 3000 | tr '\n' ' ')
# 		--error-exitcode=1 ./$(NAME) "17 3 22 8 14 87 25 1 19 36 6 11 23 9 16 4 20 12 7 28 35 24 2 15 10 21 5 18 13"


.PHONY: all clean fclean re
