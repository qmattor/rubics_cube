CC := g++
NAME := Rubics_cube
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c++14 -D GL_SILENCE_DEPRECATION
LINT := cpplint
LINT_FLAGS := --filter=-runtime/references,-build/c++11,-build/include_what_you_use,-build/include_order,-build/header_guard --root=.
DEBUG_PARAM :=
HEADERS := headers/libqm.hpp headers/matrix.hpp headers/random.hpp headers/rubics.hpp headers/timer.hpp headers/cube.hpp
LINKS :=
SRC := src/rubics.cpp src/cube.cpp
SOURCE := src/main.cpp $(SRC)
ALL_SRC := $(SOURCE) $(HEADERS)
TEST := src/test.cpp $(SRC)


OBJECTS := $(patsubst %.cpp,%.o,$(SOURCE))
TEST_OBJ := $(patsubst %.cpp,%.o,$(TEST))
ALL_OBJ := $(patsubst %.cpp,%.o,$(SOURCE))


all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): lint $(OBJECTS)
	$(CC) $(LIBFT) $(OBJECTS) $(CFLAGS) $(LINKS) -o $(NAME) -framework GLUT -framework OpenGL

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



