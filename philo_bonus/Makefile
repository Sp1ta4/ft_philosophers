.DEFAULT_GOAL := all

NAME = philo_bonus
SRC_DIR = src
INCLUDE = -I includes

SRCS = $(shell find $(SRC_DIR) -maxdepth 1 -name "*.c")

OBJS = $(SRCS:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -pthread -g3 -fsanitize=thread #-fsanitize=thread

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 