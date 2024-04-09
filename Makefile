NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror #-fsanitize=address -g -static-libsan
LIBFT_DIR	:= ./libft

HEADERS	:= -I $(LIBFT)/include
READLINE	:= -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LIBFT	:= $(LIBFT_DIR)/libft.a
SRCS	:= 	minishell.c \
			init.c \
			parser.c \
			parse_redirs.c \
			parse_cmd_n_args.c \
			parse_utils.c \
			execute.c \
			redirection.c \
			paths.c \
			expand.c \
			builtins.c \
			export.c \
			unset.c \
			array_utils.c \
			cd.c \
			pipes.c \
			heredoc.c \
			signals.c \
			free.c \
			error.c \
			error_helper.c \
			parse_quotes.c \
			parse_spaces.c \
			syntax.c \
			exit.c \
			validate_cmd.c \
			echo.c

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(HEADERS) $(READLINE) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
