/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:38:36 by mdogadin          #+#    #+#             */
/*   Updated: 2024/04/03 17:00:07 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_signal_status;

char	*ft_get_strs(char *str[2], char *limit)
{
	size_t	len;

	len = 0;
	while (g_signal_status != 130 && (!str[0] || ft_strncmp(str[0], limit, len)
			|| ft_strlen(limit) != len))
	{
		str[1] = ft_strjoin(str[1], str[0]);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
			break ;
		len = ft_strlen(str[0]);
		str[0] = ft_strjoin(str[0], "\n");
	}
	free(str[0]);
	return (str[1]);
}

int	virtual_doc(char *str[2], char *name)
{
	int	fd[2];

	g_signal_status = 0;
	if (pipe(fd) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return (-1);
	}
	str[1] = ft_get_strs(str, name);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_signal_status == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
