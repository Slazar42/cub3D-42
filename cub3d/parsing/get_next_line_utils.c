/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 23:01:28 by slazar            #+#    #+#             */
/*   Updated: 2023/11/21 22:28:31 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*my_strjoin(char *save, char *buffer)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(my_strlen(save) + my_strlen(buffer) + 1);
	if (!str)
		return (0);
	i = 0;
	while (save && save[i])
	{
		str[i] = save[i];
		i++;
	}
	j = 0;
	while (buffer && buffer[j])
	{
		str[i + j] = buffer[j];
		j++;
	}
	str[i + j] = '\0';
	if (save)
		free(save);
	return (str);
}

int	my_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
