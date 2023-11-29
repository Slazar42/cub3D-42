/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:33:05 by slazar            #+#    #+#             */
/*   Updated: 2023/11/29 16:45:17 by slazar           ###   ########.fr       */
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

char	*ft_strdup(char *src, int size)
{
	int		index;
	char	*dest;
	char	*d;

	index = 0;
	d = ((dest = (char *)malloc(size * sizeof(char) + 1)));
	if (!d)
		return (NULL);
	while (index < size)
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

void init_null(t_map **map)
{
	(*map)->no = NULL;
	(*map)->so = NULL;
	(*map)->we = NULL;
	(*map)->ea = NULL;
	(*map)->ceiling_rgb = NULL;
	(*map)->floor_rgb = NULL;
	(*map)->count = 0;
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
	if (str[i] == '\n' || str[i] == '\0')
		return (-1);
	return (i);
}
int campare(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str && str2 && str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (1);
		i++;
	}
	if (str[i] == str2[i])
		return (0);
	return (1);
}

void take_and_check(char **s, char *str)
{
	if (*s != NULL)
		ft_error("\x1b[31mError\n\x1b[0mDuplicate texture\n");
	*s = ft_strdup(str, my_strlen(str));
}

int tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_line_tab(char **tab, t_map **map)
{
	if (tab_len(tab) == 2 && (!campare(tab[0], "NO") || !campare(tab[0], "SO") 
		|| !campare(tab[0], "WE") || !campare(tab[0], "EA")))
	{
		if (!campare(tab[0], "NO"))
			take_and_check(&(*map)->no, tab[1]);
		else if (!campare(tab[0], "SO"))
			take_and_check(&(*map)->so, tab[1]);
		else if (!campare(tab[0], "WE"))
			take_and_check(&(*map)->we, tab[1]);
		else if (!campare(tab[0], "EA"))
			take_and_check(&(*map)->ea, tab[1]);
		(*map)->count+=1;
		return (0);
	}
	if(!campare(tab[0], "F") || !campare(tab[0], "C"))
	{
		(*map)->count+=1;
		return (0);
	}
	return (1);
}
int valid_line(char **tab, char *str)
{
	int i;
	int c;
	
	i = -1;
	c = 0;
	while (str[++i])
		if (str[i] == ',')
			c++;
	if (c != 2)
		return (1);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == ',' 
		|| str[i] == '\n' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] != '\0')
		return (1);
	if(tab_len(tab) != 3)
		return (1);
	return (0);
}
int ft_atoi2(char *str)
{
	int	nb;
	int i;
	
	i = 0;
	nb = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}
int *ft_atoi(char **tab)
{
	int	*rgb;
	int	i;

	i = 0;
	rgb = malloc(sizeof(int) * 3);

	while (tab[i])
	{
		rgb[i] = ft_atoi2(tab[i]);
		i++;
	}
	return (rgb);
}
void free_this(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void 	take_f_c(t_map **map, int i, char *str, char *fc)
{
	int j;
	char **tab;

	j = 0;
	while((*map)->map[i][j] == ' ' || (*map)->map[i][j] == '\t' 
		|| (*map)->map[i][j] == 'F' || (*map)->map[i][j] == 'C')
		j++;
	tab = original_split(str + j, ',');
	if(valid_line(tab,str + j))
		ft_error("\x1b[31mError\n\x1b[0mInvalid line in map\n");
	if(fc[0] == 'C' && !(*map)->ceiling_rgb)
		(*map)->ceiling_rgb = ft_atoi(tab);
	else if(fc[0] == 'F' && !(*map)->floor_rgb)
		(*map)->floor_rgb = ft_atoi(tab);
	else if ((*map)->ceiling_rgb || (*map)->floor_rgb)
		ft_error("\x1b[31mError\n\x1b[0mDuplicate floor or ceiling\n");
	free_this(tab);
}


void	no_so_we_ea(t_map **map)
{
	int		i;
	char	**tab;
	i = -1;
	while ((*map)->map[++i])
	{
		if (empty_line((*map)->map[i]) == -1)
			continue ;
		tab = my_split((*map)->map[i]);
		if(check_line_tab(tab, map) && (*map)->count < 6)
			ft_error("\x1b[31mError\n\x1b[0mInvalid line in map\n");
		if(!campare(tab[0], "F") || !campare(tab[0], "C"))
			take_f_c(map, i, (*map)->map[i], tab[0]);
		free_this(tab);
	}
	i = -1;
	while (++i < 3)
	{
		if((*map)->ceiling_rgb[i] > 255 || (*map)->ceiling_rgb[i] < 0)
			ft_error("\x1b[31mError\n\x1b[0mInvalid ceiling color\n");
		if((*map)->floor_rgb[i] > 255 || (*map)->floor_rgb[i] < 0)
			ft_error("\x1b[31mError\n\x1b[0mInvalid floor color\n");
	}
}

void	check_map (t_map *map)
{
	init_null(&map);
	no_so_we_ea(&map);
	map_test(&map);
}

int	main(int ac, char **av)
{
	t_map	map;

	check_args(ac, av, &map);
	read_map(&map);
	check_map(&map);
	system("leaks cub3D");
}
