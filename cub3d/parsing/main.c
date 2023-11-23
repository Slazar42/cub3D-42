/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:33:05 by slazar            #+#    #+#             */
/*   Updated: 2023/11/23 22:31:00 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(1);
}
void	map_height(t_map **map)
{
	char	*line;

	while (1)
	{
		line = get_next_line((*map)->fd_map);
		if (line == NULL)
			break ;
		(*map)->map_height++;
		free(line);
	}
	close((*map)->fd_map);
	(*map)->fd_map = open((*map)->map_path, O_RDONLY);
	(*map)->map = ft_calloc(((*map)->map_height + 1), sizeof(char *));
	(*map)->map[(*map)->map_height] = NULL;
}

int	read_map(t_map *map)
{
	int	i;

	i = 0;
	map_height(&map);
	while (1)
	{
		map->map[i] = get_next_line(map->fd_map);
		if (map->map[i++] == NULL)
			break ;
		printf("%s", map->map[i - 1]);
	}
	close(map->fd_map);
	return (0); 
}

int	check_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b' || str[i - 2] != 'u' 
		|| str[i - 3] != 'c' || str[i - 4] != '.')
		return (1);
	return (0);
}

char	*ft_strdup(char *src)
{
	int		index;
	char	*dest;
	char	*d;

	index = 0;
	d = ((dest = (char *)malloc(my_strlen(src) * sizeof(char) + 1)));
	if (!d)
		return (NULL);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

void	check_args(int ac, char	**av, t_map *map)
{
	map->map_path = av[1];
	map->fd_map = open(map->map_path, O_RDONLY);
	if (ac != 2)
		ft_error("\x1b[31mError\n\x1b[33mTry :\x1b[0m ./cub3D maps/MapName.cub\n");
	if (check_path(map->map_path))
		ft_error("\x1b[31mError\n\x1b[0mFile extension must be .cub\n");
	if (map->fd_map == -1)
		ft_error("\x1b[31mError\n\x1b[0mCan't open the file \n");
}

void	skip_spaces(char *str, int *j)
{
	while (str[*j] == ' ' || str[*j] == '\t')
		(*j)++;
}

void	skip_new_line(char *str, int *i)
{
	while (str[*i] == '\n')
		(*i)++;
}

void init_null(t_map **map)
{
	(*map)->no = NULL;
	(*map)->so = NULL;
	(*map)->we = NULL;
	(*map)->ea = NULL;
	(*map)->i = 0;
	(*map)->j = 0;
	(*map)->flag = 0;
	(*map)->f = 0;
	(*map)->c = 0;
	(*map)->r = 0;
}
void	*ft_calloc(int count, int size)
{
	char	*memory;
	int		i;

	i = 0;
	memory = malloc(count * size);
	if (memory == NULL)
		return (0);
	while (i < count * size)
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}

int empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '\n')
		return (-1);
	return (i);
}
int	check_line_tab(char **tab, t_map **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	if (((tab[0][0] == 'N' && tab[0][1] == 'O' ) || (tab[0][0] == 'S' && tab[0][1] == 'O') || (tab[0][0] == 'W' && tab[0][1] == 'E') || (tab[0][0] == 'E' && tab[0][1] == 'A')) && tab[0][2] == '\0' && tab[1] != NULL && tab[2] == NULL)
	{
		if (tab[0][0] == 'N' && tab[0][1] == 'O')
		{
			if((*map)->no != NULL)
				ft_error("\x1b[31mError\n\x1b[0mDuplicate NO texture\n");
			(*map)->no = ft_strdup(tab[1]);
		}
		if (tab[0][0] == 'S' && tab[0][1] == 'O')
		{
			if((*map)->so != NULL)
				ft_error("\x1b[31mError\n\x1b[0mDuplicate SO texture\n");
			(*map)->so = ft_strdup(tab[1]);
		}
		if (tab[0][0] == 'W' && tab[0][1] == 'E')
		{
			if((*map)->we != NULL)
				ft_error("\x1b[31mError\n\x1b[0mDuplicate WE texture\n");	
			(*map)->we = ft_strdup(tab[1]);
		}
		if (tab[0][0] == 'E' && tab[0][1] == 'A')
		{
			if((*map)->ea != NULL)
				ft_error("\x1b[31mError\n\x1b[0mDuplicate EA texture\n");	
			(*map)->ea = ft_strdup(tab[1]);
		}
	}
	return (0);
}

void	no_so_we_ea(t_map **map)
{
	char	**tab;
	int		i;
	int		j;
	i = 0;
	j = 0;
	init_null(map);
	while ((*map)->map[i])
	{
		if (empty_line((*map)->map[i]) == -1)
			i++;
		else
		{
			tab = my_split((*map)->map[i]);
			if(check_line_tab(tab, map))
				ft_error("\x1b[31mError\n\x1b[0mInvalid line in map\n");
		}
	}
}

void	check_map (t_map *map)
{
	no_so_we_ea(&map);
	// f_c(&map );
	// map_test(&map);
}

int	main(int ac, char **av)
{
	t_map	map;

	check_args(ac, av, &map);
	read_map(&map);
	check_map(&map);
}
