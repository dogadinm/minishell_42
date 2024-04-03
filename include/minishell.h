/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:06:46 by mdogadin          #+#    #+#             */
/*   Updated: 2024/04/03 17:09:02 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GREEN "\001\033[1;92m\002"
# define MAGENTA "\001\033[1;95m\002"
# define RED "\001\033[1;91m\002"
# define DEFAULT "\001\033[0;39m\002"
# define BLUE "\001\033[1;94m\002"

# include "../libft/inc/libft.h"
# include "get_next_line.h"
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_command_info
{
	t_list	*cmd;
	char	**envp;
	pid_t	pid;
}	t_command_info;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

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

// get_params 
t_mini	*get_outfile1(t_mini *mode, char **args, int *i);
t_mini	*get_outfile2(t_mini *node, char **args, int *i);
t_mini	*get_infile1(t_mini *node, char **args, int *i);
t_mini	*get_infile2(t_mini *node, char **args, int *i);

//env
char	*get_env(char *var, char **envp, int n);
char	**set_env(char *var, char *value, char **envp, int n);
int		mini_export(t_command_info *command);
int		mini_unset(t_command_info *command);

// errors
int		mini_exit(t_list *cmd, int *is_exit);
void	cd_error(char **str[2]);
void	free_content(void *content);
void	*mini_perror(int err_type, char *param, int err);

// exec
void	*check_to_fork(t_command_info *command, t_list *cmd, int fd[2]);

// strtrim_all
char	*ft_strtrim_all(char const *string, int squote, int dquote);

// get_command_name
char	*get_command_name(t_command_info command);

// get_execve
void	get_execve(char ***out, char *full, char *args, char **envp);

// signal
void	signal_new_line(int sign);

// virtual_doc
int		virtual_doc(char *str[2], char *name);

//tomas
//parse args
void	*check_args(char *out, t_command_info *p);

//builtins
int		builtin(t_command_info *prompt, t_list *cmd, int *is_exit, int n);
int		is_builtin(t_mini *n);

//shell commands
int		mini_cd(t_command_info *prompt);
int		mini_pwd(void);
int		mini_echo(t_list *cmd);

//fill nodes
t_list	*fill_nodes(char **args, int i);

//execute command
void	*exec_cmd(t_command_info *prompt, t_list *cmd);
void	get_cmd(t_command_info *prompt, t_list *start,
			char **split_path, char *path);

//trim
char	**ft_cmdtrim(char const *s, char *set);

//subsplit
char	**ft_cmdsubsplit(char const *s, char *set);

//expand vars
char	*expand_vars(char *str, int i, int quotes[2], t_command_info *prompt);
char	*expand_path(char *str, int i, int quotes[2], char *var);

#endif