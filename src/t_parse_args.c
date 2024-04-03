/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parse_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:38:33 by mdogadin          #+#    #+#             */
/*   Updated: 2024/04/03 16:38:33 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_signal_status;

static char	**split_all(char **args, t_command_info *command)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, command);
		args[i] = expand_path(args[i], -1, quotes, \
			get_env("HOME", command->envp, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

static void	*parse_args(char **args, t_command_info *p)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	p->cmd = fill_nodes(split_all(args, p), -1);
	if (!p->cmd)
		return (p);
	i = ft_lstsize(p->cmd);
	g_signal_status = builtin(p, p->cmd, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_signal_status, 0);
	if (!is_exit && g_signal_status == 13)
		g_signal_status = 0;
	if (g_signal_status > 255)
		g_signal_status = g_signal_status / 255;
	if (args && is_exit)
	{
		ft_lstclear(&p->cmd, free_content);
		return (NULL);
	}
	return (p);
}

void	*check_args(char *out, t_command_info *p)
{
	char	**a;
	t_mini	*n;

	if (!out)
	{
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ");
	free(out);
	if (!a)
		mini_perror(QUOTE, NULL, 1);
	if (!a)
		return ("");
	p = parse_args(a, p);
	printf("hh\n");
	if (p && p->cmd)
		n = p->cmd->content;
	if (p && p->cmd && n && n->full_cmd && ft_lstsize(p->cmd) == 1)
		p->envp = set_env("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1], \
			p->envp, 1);
	if (p && p->cmd)
		ft_lstclear(&p->cmd, free_content);
	return (p);
}
