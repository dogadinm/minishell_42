/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchvatal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:03:35 by tchvatal          #+#    #+#             */
/*   Updated: 2024/04/03 21:03:37 by tchvatal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstget_at(t_list *lst, int i)
{
	t_list	*target;
	int		j;

	j = 0;
	if (!lst)
		return (NULL);
	while (lst && j++ < i)
		lst = lst->next;
	target = lst;
	return (target);
}
