/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:58:51 by rcannars          #+#    #+#             */
/*   Updated: 2024/12/16 14:03:16 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	s_len;

	s_len = ft_strlen(s) + 1;
	d = malloc(s_len * sizeof(char));
	if (d == NULL)
		return (NULL);
	ft_strlcpy(d, s, s_len);
	return (d);
}
