/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:57:44 by slazar            #+#    #+#             */
/*   Updated: 2023/11/20 02:39:16 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*my_filter(char *save)
{
	char	*fil;
	int		i;

	i = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (!save[i])
		fil = malloc (i + 1);
	else
		fil = malloc (i + 2);
	if (!fil)
		return (0);
	i = 0;
	while (save[i] != '\n' && save[i])
	{
		fil[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		fil[i++] = '\n';
	fil[i] = '\0';
	return (fil);
}

char	*my_filter_cut(char *save)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (save[i] == '\n')
		i++;
	p = malloc(my_strlen(save) - i + 1);
	while (save[i])
		p[j++] = save[i++];
	p[j] = '\0';
	free(save);
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buffer;
	int			readed;
	char		*fil;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!my_strchr(save, '\n'))
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
			break ;
		buffer[readed] = '\0';
		save = my_strjoin(save, buffer);
	}
	free(buffer);
	if (my_strlen(save) > 0 && readed >= 0)
	{
		fil = my_filter(save);
		save = my_filter_cut(save);
		return (fil);
	}
	free(save);
	return (save = 0);
}
