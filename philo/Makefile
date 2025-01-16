CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = philo

SRCS = src/main.c src/error_handler.c src/utils.c

OBJS = $(SRCS:.c=.o)
BOBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
