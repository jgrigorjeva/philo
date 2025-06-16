CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread 

SRC = main.c parse_input.c print.c init.c time.c routine.c end.c eat.c \
	utils.c utils2.c monitor.c assign_forks.c

OBJS = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re