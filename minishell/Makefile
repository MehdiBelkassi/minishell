NAME	=	minishell
SRC		=	main.c signals.c libft/strtrim.c parsing/tokenizer.c parsing/tokenizer_utils.c parsing/c_tokenizer.c \
			parsing/build_tree.c parsing/free.c parsing/build_tree_utilis.c parsing/parser.c \
			parsing/env.c parsing/expand.c built-in/check_builtins.c libft/libft_utils3.c\
			built-in/echo.c built-in/pwd.c built-in/env.c built-in/exit.c built-in/export.c built-in/unset.c built-in/export_utils.c \
			built-in/cd.c execution/execute_tree.c parsing/heredoc.c execution/execute_cmd.c execution/execute_pipe.c\
			execution/execute_cmd_utils.c execution/execute_redir.c parsing/build_tree_redir.c parsing/c_tokenizer_utils.c parsing/expand_utils.c\
			parsing/parser_utils.c parsing/ambiguous.c libft/ft_split.c libft/ft_strjoin.c libft/libft_utils2.c execution/execute_cmd_utils2.c\
			execution/execute_pipe_utils.c parsing/expand_heredoc.c

HD		= 	par.h token.h tree.h
OBJ		=	$(SRC:%.c=%.o)
CC		=	cc -Wall -Wextra -Werror
LDFLAGS= -L/Users/aben-moh/Desktop/readline/8.3.1/lib
CPPFLAGS= -I/Users/aben-moh/Desktop/readline/8.3.1/include
LDLIBS	= -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

%.o: %.c HD
		$(CC) $(CPPFLAGS) -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all