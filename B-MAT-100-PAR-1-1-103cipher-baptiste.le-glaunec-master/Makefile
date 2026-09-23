##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

CC		=	gcc

SRC		=	src/verif_arg.c	\
			src/get_determinant.c	\
			src/reverse_key.c	\

SRC_TEST	=	\

OBJ		=	$(SRC:.c=.o)

OBJ_TEST	=	$(SRC_TESTS:.c=.o)

LIB		=	-L./lib/my/ -lmy

INCLUDE		=	-Iinclude

CRITERION	=	-lcriterion --coverage

CPPFLAGS	=	-Wall -Wextra -g3

NAME		=	103cipher

TEST_NAME	=	test_run

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) main.c $(OBJ) $(INCLUDE)

tests_run: clean
	$(CC) -o $(TEST_NAME) $(SRC_TEST) $(SRC) $(INCLUDE) $(CPPFLAGS) $(LIB) $(CRITERION)
	./test_run

clean:
	find -name 'libmy.a' -delete
	find -name '*~' -delete
	find -name '*.o' -delete
	find -name '*.gcda' -delete
	find -name '*.gcno' -delete
	find -name '#*#' -delete

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all
