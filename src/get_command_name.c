/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:38:03 by mdogadin          #+#    #+#             */
/*   Updated: 2024/04/03 16:56:17 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_signal_status;

static void	get_home(t_command_info command, char **path)
{
	char	*temp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = get_env("HOME", command.envp, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(temp);
	}
	free(home);
	home = ft_strjoin(BLUE, pwd);
	free(pwd);
	pwd = ft_strjoin(":", home);
	free(home);
	*path = ft_strjoin(DEFAULT, pwd);
	free(pwd);
}

static void	get_user(t_command_info command, char **user)
{
	char	**temp;

	temp = NULL;
	get_execve(&temp, "/usr/bin/whoami", "whoami", command.envp);
	if (!temp)
		temp = ft_extend_matrix(temp, "guest");
	if (!ft_strncmp(temp[0], "root", 4))
		*user = ft_strjoin(RED, *temp);
	else if (temp[0])
		*user = ft_strjoin(MAGENTA, *temp);
	ft_free_matrix(&temp);
}

char	*get_command_name(t_command_info command)
{
	char	*temp;
	char	*user;
	char	*path;
	char	*user_path;

	get_user(command, &temp);
	user = ft_strjoin(temp, "@minishell");
	free(temp);
	get_home(command, &path);
	temp = ft_strjoin(user, path);
	free(user);
	free(path);
	if (!g_signal_status || g_signal_status == -1)
		user_path = ft_strjoin(temp, DEFAULT);
	else
		user_path = ft_strjoin(temp, RED);
	free(temp);
	temp = ft_strjoin(user_path, "$ ");
	free(user_path);
	user_path = ft_strjoin(temp, DEFAULT);
	free(temp);
	return (user_path);
}
