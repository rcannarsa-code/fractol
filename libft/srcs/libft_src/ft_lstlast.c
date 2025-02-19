/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:47:46 by rcannars          #+#    #+#             */
/*   Updated: 2024/12/11 16:48:04 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*c_node;

	c_node = lst;
	if (!c_node)
		return (NULL);
	while (c_node->next != NULL)
		c_node = c_node->next;
	return (c_node);
}
