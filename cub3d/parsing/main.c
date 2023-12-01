/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:33:05 by slazar            #+#    #+#             */
/*   Updated: 2023/12/01 14:53:10 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void init_null(t_map **map)
{
	(*map)->no = NULL;
	(*map)->so = NULL;
	(*map)->we = NULL;
	(*map)->ea = NULL;
	(*map)->map_height = 0;
	(*map)->ceiling_rgb = NULL;
	(*map)->floor_rgb = NULL;
	(*map)->count = 0;
}
int	read_map(t_map *map)
{
	int	i;

	i = 0;
	init_null(&map);
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

int map_1_0(char *str)
{
	int i;
	
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if(str[i] == '1' || str[i] == '0')
		return (1);
	return (0);
}

void	map_in_m(t_map **map)
{
	int i;
	int c;
	int j;
	
	j = -1;
	i = -1;
	c = 0;
	while ((*map)->map[++i])
		if (map_1_0((*map)->map[i]))
			break;
	while ((*map)->map[--(*map)->map_height])
		if (map_1_0((*map)->map[(*map)->map_height]))
			break;
	(*map)->m_size = (*map)->map_height - i + 1;
	(*map)->m = ft_calloc(((*map)->m_size + 1), sizeof(char *));
	while (++j < (*map)->map_height - i + 1)
		(*map)->m[j] = ft_strdup((*map)->map[i + j], my_strlen((*map)->map[i + j]));
	(*map)->m[j] = NULL;
	free_this((*map)->map);
}
void	map_positions(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->m[++i])
	{
		j = -1;
		while (map->m[i][++j])
		{
			if (map->m[i][j] == 'N' || map->m[i][j] == 'S' 
				|| map->m[i][j] == 'E' || map->m[i][j] == 'W')
			{
				map->p_x = i;
				map->p_y = j;
				map->p_direction = map->m[i][j];
			}
		}
	}
}
void	map_test(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->m[++i])
	{
		if(empty_line(map->m[i]) == -1)
			ft_error("\x1b[31mError\n\x1b[0mEmpty line in map\n");
		j = -1;
		while (map->m[i][++j])
		{
			if (map->m[i][j] != ' ' && map->m[i][j] != '1' 
				&& map->m[i][j] != '0'  && map->m[i][j] != 'W' 
				&& map->m[i][j] != 'N' && map->m[i][j] != 'S' 
				&& map->m[i][j] != 'E' && map->m[i][j] != '\n')
					ft_error("\x1b[31mError\n\x1b[0mInvalid character in map\n");
		}
	}
}

int len(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	while (str[--i] == ' ');
	return (i+1);
}

bool is_valid(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

void	valid_path(t_map *map)
{
	int i;
	int j;
	
	i = -1;
	while (map->m[++i])
	{
		j = -1;
		while (map->m[i][++j] != '\n' && map->m[i][j] != '\0')
		{
			if (is_valid(map->m[i][j]))
			{
				if (i == 0 || i == map->m_size - 1 || j == 0 || j == len(map->m[i]) - 1 
				|| map->m[i][j + 1] == ' ' || map->m[i][j - 1] == ' ' 
				|| map->m[i + 1][j] == ' ' || map->m[i - 1][j] == ' ')
					ft_error("\x1b[31mError\n\x1b[0mInvalid map\n");
			}
		}
	}
}

void	check_map (t_map *map)
{
	no_so_we_ea(&map);
	map_in_m(&map);
	map_test(map);
	map_positions(map);
	valid_path(map);
}

int	main(int ac, char **av)
{
	t_map	map;

	check_args(ac, av, &map);
	read_map(&map);
	check_map(&map);
	system("leaks cub3D");
}
