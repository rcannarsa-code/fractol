/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:01:14 by rcannars          #+#    #+#             */
/*   Updated: 2024/12/11 17:01:30 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp_node;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		tmp_node = *lst;
		*lst = tmp_node->next;
		ft_lstdelone(tmp_node, del);
	}
}
