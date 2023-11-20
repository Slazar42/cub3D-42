/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:33:05 by slazar            #+#    #+#             */
/*   Updated: 2023/11/20 06:39:41 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void read_and_check()
{
	char	*line;
	int		fd;

	fd = open("maps/map1.cub", O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
	close(fd);
}
void	check_args(int ac,char **av)
{
	
}
int main(int ac, char **av)
{
	t_map	map;

	check_args(ac, av);
	read_and_check(&map);
}