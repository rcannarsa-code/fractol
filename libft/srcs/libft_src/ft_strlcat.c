/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:05:40 by rcannars          #+#    #+#             */
/*   Updated: 2024/12/16 14:17:23 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	if (!dest && size == 0)
		return (ft_strlen(src));
	d_len = 0;
	s_len = 0;
	i = 0;
	while (dest[d_len] && d_len < size)
	{
		d_len++;
	}
	s_len = ft_strlen(src);
	if (d_len >= size)
		return (size + s_len);
	while (src[i] && (d_len + i + 1) < size)
	{
		dest[d_len + i] = src[i];
		i++;
	}
	dest[d_len + i] = '\0';
	return (d_len + s_len);
}
