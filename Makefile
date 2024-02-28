NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
LIBFT_DIR	:= ./libft

HEADERS	:= -I $(LIBFT)/include -I /opt/Homebrew/opt/readline/include
LIBFT	:= $(LIBFT_DIR)/libft.a
SRCS	:= 	minishell.c \
			parser.c \
			debug.c
			
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(HEADERS) -lreadline -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re