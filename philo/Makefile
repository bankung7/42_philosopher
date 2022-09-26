NAME = philo

CC = gcc -g

CFLAGS = -Wall -Werror -Wextra
O_FLAGS = -lpthread

RM = rm -rf

INC = -Iinc

SRCS_DIR = srcs/
SRCS = main.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p objs/
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
