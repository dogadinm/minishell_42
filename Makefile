
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBFT = libft/libft.a
LDLIBS = -lreadline
LIBFT_DIR = ./libft


SRC = src/main.c src/builtins.c src/ft_strtrim_all.c src/exec.c			\
	  src/fill_node.c src/get_params.c src/ft_cmdtrim.c				\
	  src/expand.c src/heredoc.c src/error.c src/env.c src/custom_cmd.c		\
	  src/prompt.c	\
	  src/ft_cmdsubsplit.c src/signal.c src/parse_args.c src/get_cmd.c \
	  src/get_next_line_utils.c src/get_next_line.c

OBJ	=	$(SRC:%.c=%.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(MAKE) -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDLIBS)
			

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
			$(MAKE) clean -C ./libft
			@$(RM) $(OBJ)
			
fclean:		clean
			$(MAKE) fclean -C ./libft
			@$(RM) $(OBJ)
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re