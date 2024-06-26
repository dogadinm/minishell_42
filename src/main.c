/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:20:52 by mdogadin          #+#    #+#             */
/*   Updated: 2024/04/03 17:14:32 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_signal_status;

void	get_pid(t_command_info *command)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mini_perror(FORKERR, NULL, 1);
		ft_free_matrix(&command->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&command->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	command->pid = pid - 1;
}

t_command_info	info_init(t_command_info command, char *str, char **argv)
{
	char	*num;

	str = getcwd(NULL, 0);
	command.envp = set_env("PWD", str, command.envp, 3);
	free(str);
	str = get_env("SHLVL", command.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	command.envp = set_env("SHLVL", num, command.envp, 5);
	free(num);
	str = get_env("PATH", command.envp, 4);
	if (!str)
		command.envp = set_env("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", command.envp, 4);
	free(str);
	str = get_env("_", command.envp, 1);
	if (!str)
		command.envp = set_env("_", argv[0], command.envp, 1);
	free(str);
	return (command);
}

t_command_info	init_command(char **argv, char **env)
{
	t_command_info	command;
	char			*str;

	str = NULL;
	command.cmd = NULL;
	command.envp = ft_dup_matrix(env);
	g_signal_status = 0;
	get_pid(&command);
	command = info_init(command, str, argv);
	return (command);
}

int	main(int argc, char **argv, char **env)
{
	t_command_info	command;
	char			*str;
	char			*out;
	int				i;

	command = init_command(argv, env);
	while (argv && argc)
	{
		signal(SIGINT, signal_new_line);
		signal(SIGQUIT, SIG_IGN);
		str = get_command_name(command);
		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		free(str);
		if (!check_args(out, &command))
			break ;
	}
	i = 0;
	while (command.envp[i])
		free(command.envp[i++]);
	free(command.envp);
	exit(g_signal_status);
}
