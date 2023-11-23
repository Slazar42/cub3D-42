/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:16:23 by slazar            #+#    #+#             */
/*   Updated: 2023/11/22 22:33:25 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s &&s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned char	*sbs;
	size_t			i;

	if (len > ft_strlen(s) - start)
		sbs = malloc(ft_strlen(s) - start + 1);
	else
		sbs = malloc(len + 1);
	if (!sbs)
		return (0);
	i = 0;
	while (s[start] && len)
	{
		sbs[i] = s[start];
		start++;
		i++;
		len--;
	}
	sbs[i] = '\0';
	return ((char *)sbs);
}

static int	word(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
	}
	return (count);
}

static int	len_word(const char *s, int i)
{
	int	len_s;

	len_s = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		i++;
		len_s++;
	}
	return (len_s);
}

char	**my_split(char const *s)
{
	char	**tab;
	int		len_s;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!s)
		return (0);
	tab = ft_calloc(word(s) + 1, sizeof(char *));
	if (!tab)
		return (0);
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		len_s = len_word(s, i);
		if (++j < word(s))
			tab[j] = ft_substr(s, i, len_s);
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
	}
	return (tab);
}
