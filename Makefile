NAME = minishell
CC = gcc
CFLAGS =  -Werror -Wextra -Wall -I.
RM = rm -rf

SRC = 	./parsing/tokenization.c \
		./parsing/parsing_quotes.c \
		./parsing/token_special.c \
		./parsing/token_special_1.c \
		./parsing/parse.c \
		./parsing/syntax_controll.c \
		./parsing/ft_expand_envp.c \
		./parsing/parse_2.c \
		./utils/single_quotes.c \
		./utils/util_1.c \
		./utils/util_2.c \
		./utils/util_3.c \
		./utils/util_4.c \
		./utils/util_5.c \
		./utils/util_6.c \
		./utils/double_quotes.c \
		./utils/ft_minishell_init.c \
		./utils/ft_exit_bits.c \
		./utils/ft_signals.c \
		./utils/free_all.c \
		./utils/free_all_2.c \
		./commands/ft_cd.c \
		./commands/ft_echo.c \
		./commands/ft_env.c \
		./commands/ft_exit.c \
		./commands/ft_export.c \
		./commands/ft_pwd.c \
		./commands/ft_unset.c \
		./execution/ft_execute.c \
		./execution/ft_builtins.c \
		./execution/ft_heredoc.c \
		./execution/ft_heredoc_utils.c \
		./execution/ft_pipe.c \
		./execution/ft_execve.c \
		./execution/ft_redirection.c \
		./init.c \
		./main.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OBJS) -lreadline  ./libft/libft.a -o $(NAME)

clean:
	@$(MAKE) -C ./libft clean
	@$(RM) $(OBJS)

fclean:
	@$(MAKE) -C ./libft fclean
	@$(RM) $(OBJS) $(NAME)

re: fclean all

.PHONY: all re clean fclean

valgrind: re
	@valgrind -s --leak-check=full --show-leak-kinds=all --log-file=output.log ./minishell