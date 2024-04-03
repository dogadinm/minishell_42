/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:26:14 by mdogadin          #+#    #+#             */
/*   Updated: 2024/04/03 16:39:41 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_signal_status;

void	child_builtin(t_command_info *command, t_mini *n, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(n) && n->full_cmd)
		execve(n->full_path, n->full_cmd, command->envp);
	else if (n->full_cmd && !ft_strncmp(*n->full_cmd, "pwd", l) \
		&& l == 3)
		g_signal_status = mini_pwd();
	else if (is_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
		g_signal_status = mini_echo(cmd);
	else if (is_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
	{
		ft_putmatrix_fd(command->envp, 1, 1);
		g_signal_status = 0;
	}
}

static void	*child_redir(t_list *cmd, int fd[2])
{
	t_mini	*node;

	node = cmd->content;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (mini_perror(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_command_info *command, t_list *cmd, int fd[2])
{
	t_mini	*n;
	int		l;

	n = cmd->content;
	l = 0;
	if (n->full_cmd)
		l = ft_strlen(*n->full_cmd);
	child_redir(cmd, fd);
	close(fd[READ_END]);
	child_builtin(command, n, l, cmd);
	ft_lstclear(&command->cmd, free_content);
	exit(g_signal_status);
}

void	exec_fork(t_command_info *command, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		mini_perror(FORKERR, NULL, 1);
	}
	else if (!pid)
		child_process(command, cmd, fd);
}

void	*check_to_fork(t_command_info *command, t_list *cmd, int fd[2])
{
	t_mini	*node;
	DIR	*dir;

	node = cmd->content;
	dir = NULL;
	if (node->full_cmd)
		dir = opendir(*node->full_cmd);
	if (node->infile == -1 || node->outfile == -1)
		return (NULL);
	if ((node->full_path && access(node->full_path, X_OK) == 0) || is_builtin(node))
		exec_fork(command, cmd, fd);
	else if (!is_builtin(node) && ((node->full_path && \
		!access(node->full_path, F_OK)) || dir))
		g_signal_status = 126;
	else if (!is_builtin(node) && node->full_cmd)
		g_signal_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
