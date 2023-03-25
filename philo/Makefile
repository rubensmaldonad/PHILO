# NAME PROGRAM #

NAME	= philo

# SOURCE.C #
SRC		= philo.c \
		  validations.c \
		  threads.c \
		  utils.c \
		  routine.c \
		  end.c

# COMPILING VARIABLES #
CC		= cc
CFLAG	= -Wall -Werror -Wextra
RM		= rm -f

$(NAME) : $(SRC)
	$(CC) $(CFLAG) $(SRC)  -o $(NAME)

# COMANDS #

all:	$(NAME)

clean:
	$(RM) $(NAME)

fclean:	clean

re:		fclean all

.PHONY: all fclean clean re
