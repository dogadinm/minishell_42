/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttomatrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchvatal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:37:02 by tchvatal          #+#    #+#             */
/*   Updated: 2024/04/03 21:37:07 by tchvatal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	**ft_lsttomatrix(t_list *lst)
{
	char	**matrix;
	t_list	*aux;
	char	*temp;

	aux = lst;
	matrix = NULL;
	while (aux)
	{
		temp = ft_strdup(aux->content);
		matrix = ft_extend_matrix(matrix, temp);
		aux = aux->next;
		free(temp);
	}
	return (matrix);
}
