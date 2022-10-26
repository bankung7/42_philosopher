NAME = philo_bonus

CC = gcc -g

CFLAGS = -Wall -Werror -Wextra
O_FLAGS = -lpthread

RM = rm -rf

INC = -Iinc

SRCS_DIR = srcs/
SRCS = main.c setup.c utils.c utils2.c process.c time.c sem.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(O_FLAGS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p objs/
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

clean:
	$(RM) $(NAME) *.dSYM

fclean: clean
	$(RM) $(OBJS_DIR)

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS_DIR) inc/
	norminette -R CheckDefine  inc/

.PHONY: all clean fclean re norm
