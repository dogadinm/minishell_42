
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBFT = libft/libft.a
LDLIBS = -lreadline
LIBFT_DIR = ./libft


SRC = src/main.c src/t_builtins.c src/ft_strtrim_all.c src/exec.c			\
	  src/t_fill_node.c src/get_params.c src/f_ft_cmdtrim.c				\
	  src/t_expand.c src/virtual_doc.c src/error.c src/env.c src/get_command_name.c		\
	  src/get_execve.c	\
	  src/t_ft_cmdsubsplit.c src/signal.c src/t_parse_args.c src/get_cmd.c \
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