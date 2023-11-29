/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   original_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:31:20 by slazar            #+#    #+#             */
/*   Updated: 2023/11/29 09:48:59 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	word_(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '\n' && s[i] == c)
			i++;
		if (s[i] && s[i] != '\n')
			count++;
		while (s[i] && s[i] != c && s[i])
			i++;
	}
	return (count);
}

int	len_word_(const char *s, char c, int i)
{
	int	len_s;

	len_s = 0;
	while (s[i] && s[i] != c && s[i] != '\n')
	{
		i++;
		len_s++;
	}
	return (len_s);
}

char	**original_split(char const *s, char c)
{
	char	**tab;
	int		len_s;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!s)
		return (0);
	tab = (char **)ft_calloc(word_(s, c) + 1, sizeof(char *));
	if (!tab)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c && s[i] != '\n')
			i++;
		len_s = len_word_(s, c, i);
		if (++j < word_(s, c))
			tab[j] = ft_substr(s, i, len_s);
		while (s[i] && s[i] != c )
			i++;
	}
	return (tab);
}