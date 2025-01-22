CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = philo_bonus

SRCS = src/main.c src/inits_bonus.c src/parse_bonus.c src/routines_bonus.c \
       src/utils_bonus.c src/time_utils_bonus.c

OBJS = $(SRCS:.c=.o)

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
