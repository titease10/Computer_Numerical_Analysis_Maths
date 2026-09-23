##
## EPITECH PROJECT, 2023
## Makfile
## File description:
## Makefile for project 202unsold
##

NAME	=	204duks

all:
		cp ducks.py $(NAME)
		chmod +x $(NAME)

clean:
		$(RM) -r __pycache__

fclean:		clean
		$(RM) $(NAME)
		$(RM) -rf ./sources/__pycache__

re:		fclean all

.PHONY: all clean fclean re