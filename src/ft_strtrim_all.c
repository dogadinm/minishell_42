/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:37:58 by mdogadin          #+#    #+#             */
/*   Updated: 2024/04/03 17:37:15 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	corret_len_malloc(char const *string)
{
	int	i;
	int	squote;
	int	dquote;
	int	count;

	i = 0;
	squote = 0;
	dquote = 0;
	count = 0;
	while (string && string[i])
	{
		squote = (squote + (!dquote && string[1] == '\'')) % 2;
		dquote = (dquote + (!squote && string[1] == '\"')) % 2;
		if ((string[i] == '\"' && !squote) || (string[i] == '\'' && !dquote))
			count++;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (count);
}

char	*ft_strtrim_all(char const *string, int squote, int dquote)
{
	char	*trimmed;
	int		count;
	int		i;
	int		j;

	i = 0;
	j = -1;
	count = corret_len_malloc(string);
	if (!string || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(string) - count + 1));
	if (!trimmed)
		return (NULL);
	while (string[i])
	{
		squote = (squote + (!dquote && string[i] == '\'')) % 2;
		dquote = (dquote + (!squote && string[i] == '\"')) % 2;
		if ((string[i] != '\'' || dquote) && (string[i] != '\"' || squote)
			&& ++j >= 0)
			trimmed[j] = string[i];
		i++;
	}
	trimmed[++j] = '\0';
	return (trimmed);
}
