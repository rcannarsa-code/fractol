/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:56:08 by rcannars          #+#    #+#             */
/*   Updated: 2024/12/16 14:19:59 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char sep)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++word_count;
		while (*s && *s != sep)
			++s;
	}
	return (word_count);
}

static void	ft_free_all(char **tab, int allocated)
{
	int	i;

	i = 0;
	while (i < allocated)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	ft_allocate(char **tab, char const *s, char sep)
{
	int			index;
	char const	*start;

	index = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		start = s;
		while (*s && *s != sep)
			++s;
		if (s > start)
		{
			tab[index] = ft_substr(start, 0, s - start);
			if (!tab[index])
			{
				ft_free_all(tab, index);
				return (0);
			}
			index++;
		}
	}
	tab[index] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		size;

	if (!s)
		return (NULL);
	size = ft_count_words(s, c);
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	ft_allocate(new, s, c);
	return (new);
}
