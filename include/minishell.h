#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

typedef struct s_command_info
{
    t_list	*cmd;
	char	**envp;
	pid_t	pid;
}	t_command_info;


enum e_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};



char **ft_matrix_dup(matrix);
void ft_free_matrix(char **matrix);
void	signal_new_line(int sign);

int	ft_strchr_i(const char *s, int c);
#endif