##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

CC		=	gcc

SRC		=	check_error.c	\
			handle_matrix.c	\
			process.c	\
			parser.c	\
			display.c	\

SRC_TEST	=	\

OBJ		=	$(SRC:.c=.o)

OBJ_TEST	=	$(SRC_TESTS:.c=.o)

INCLUDE		=	-Iincludes

MATH		=	-lm

CRITERION	=	-lcriterion --coverage

CPPFLAGS	=	-Wall -Wextra -g3

NAME		=	102architect

TEST_NAME	=	test_run

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) main.c $(OBJ) $(INCLUDE) $(MATH)

tests_run: clean
	$(CC) -o $(TEST_NAME) $(SRC_TEST) $(SRC) $(INCLUDE) $(MATH) $(CPPFLAGS) $(CRITERION)
	./test_run

clean:
	find -name '*~' -delete
	find -name '*.o' -delete
	find -name '*.gcda' -delete
	find -name '*.gcno' -delete
	find -name '#*#' -delete

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all
