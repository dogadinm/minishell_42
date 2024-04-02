NAME = libft.a
CC = gcc 
CFLAGS = -Wall -Wextra -Werror
AR = ar 

SRC =	src/ft_atoi.c src/ft_bzero.c	\
	src/ft_calloc.c src/ft_putendl_fd.c		\
	src/ft_itoa.c src/ft_putchar_fd.c		\
	src/ft_putstr_fd.c src/ft_memccpy.c		\
	src/ft_memchr.c src/ft_memcmp.c			\
	src/ft_memcpy.c src/ft_isalnum.c		\
	src/ft_isalpha.c src/ft_isascii.c		\
	src/ft_isdigit.c src/ft_isprint.c		\
	src/ft_memmove.c src/ft_memset.c		\
	src/ft_split.c src/ft_strchr.c			\
	src/ft_strdup.c src/ft_strjoin.c		\
	src/ft_strlcat.c src/ft_strlcpy.c		\
	src/ft_strlen.c src/ft_strmapi.c		\
	src/ft_strncmp.c src/ft_strnstr.c		\
	src/ft_strrchr.c src/ft_strtrim.c		\
	src/ft_substr.c src/ft_tolower.c		\
	src/ft_toupper.c src/ft_putnbr_fd.c

LIST = list/ft_lstadd_back.c	\
	list/ft_lstadd_front.c	\
	list/ft_lstclear.c		\
	list/ft_lstdelone.c		\
	list/ft_lstiter.c		\
	list/ft_lstlast.c		\
	list/ft_lstsize.c		\
	list/ft_lstnew.c			\
	list/ft_lstmap.c			\
	list/ft_lstget_at.c

UTIL = util/ft_putnbr_base_fd.c util/ft_putstrn_fd.c		\
	util/ft_putnchar_fd.c util/ft_isspace.c util/ft_uitoa.c	\
	util/ft_nbrlen.c util/ft_strrncmp.c util/ft_countchar.c	\
	util/ft_strenlarge.c util/ft_recursive_power.c			\
	util/ft_chartostr.c util/ft_sqrt.c util/ft_newvector.c	\
	util/ft_euclideandistance.c  util/ft_atoi2.c			\
	util/ft_free_matrix.c util/ft_dup_matrix.c				\
	util/ft_strchr_i.c util/ft_putmatrix_fd.c				\
	util/ft_matrixlen.c util/ft_strchars_i.c				\
	util/ft_between_chars.c util/ft_subsplit.c				\
	util/ft_extend_matrix.c util/ft_matrixtolst.c			\
	util/ft_lsttomatrix.c util/ft_matrix_replace_in.c 		\
	util/ft_matrixlen.c

OBJ = $(SRC:.c=.o)

OBJ_LIST = $(LIST:.c=.o)

OBJ_UTIL = $(UTIL:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_LIST) $(OBJ_UTIL)
	$(AR) rc $(NAME) $(OBJ) $(OBJ_LIST) $(OBJ_UTIL)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_LIST) $(OBJ_UTIL)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus