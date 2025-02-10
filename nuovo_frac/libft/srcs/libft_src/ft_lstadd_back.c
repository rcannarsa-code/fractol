/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:52:35 by rcannars          #+#    #+#             */
/*   Updated: 2024/12/11 16:52:56 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*l_node;

	if (!new)
		return ;
	l_node = ft_lstlast(*lst);
	if (!l_node)
	{
		*lst = new;
		return ;
	}
	l_node->next = new;
}
