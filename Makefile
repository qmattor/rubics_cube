CC := g++
NAME := Rubics_cube
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c++14
LINT := cpplint
LINT_FLAGS := --filter=-runtime/references,-build/c++11,-build/include_what_you_use,-build/include,-whitespace/tab --root=.
DEBUG_PARAM :=
HEADERS := libqm.hpp matrix.hpp random.hpp rubics.hpp timer.hpp
LINKS :=
SRC := rubics.cpp
SOURCE := main.cpp $(SRC)
ALL_SRC := $(SOURCE) $(HEADERS)
TEST := test.cpp $(SRC)


OBJECTS := $(patsubst %.cpp,%.o,$(SOURCE))
TEST_OBJ := $(patsubst %.cpp,%.o,$(TEST))
ALL_OBJ := $(patsubst %.cpp,%.o,$(SOURCE))


all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): lint $(OBJECTS)
	$(CC) $(LIBFT) $(OBJECTS) $(CFLAGS) $(LINKS) -o $(NAME)

tests: test
test: $(TEST_OBJ)
	$(CC) $(LIBFT) $(TEST_OBJ) $(CFLAGS) -lboost_unit_test_framework -o tests

lint: $(ALL_SRC)
	$(LINT) $(LINT_FLAGS) $^

debug:
	$(CC) $(SOURCE) $(LIBFT) $(CFLAGS) $(LINKS) -g -o $(NAME)
	valgrind --leak-check=full ./$(NAME) $(DEBUG_PARAM)

clean:
	rm -f test.o
	rm -f $(ALL_OBJ)

fclean: dclean
	rm -f $(NAME)
	rm -f test.o
	rm -f tests

dclean: clean
	rm -rf $(NAME).dSYM

re: fclean all



