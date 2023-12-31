/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:02:59 by slazar            #+#    #+#             */
/*   Updated: 2023/12/09 21:56:30 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

typedef struct t_player 
{
	void			*mlx;
	void			*win;
	// mlx_image_t		*image;
	char			**map;
	double			player_x;
	double			player_y;
	double			plane_x;
	double			plane_y;
	double			direction;
	double			rotationangle;
	double			movespeed;
	double			rotationspeed;
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			key_left;
	bool			key_right;
	double			new_x;
	double			new_y;
}t_player;

typedef struct s_rays
{
	double	end_point;
	double	start_point;
	int		vert_hori;
	int		left_right;
}t_rays;

/*---------------------------parsing---------------------------------*/
/*---------------------------parsing---------------------------------*/

typedef struct s_map
{
	char	**map;
	char 	**m;
	int		m_size;
	int		count;
	int		p_x;
	int		p_y;
	char 	p_direction;
	int		player_count;
	char	*map_path;
	int		map_width;
	int		map_height;
	int		fd_map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int 	*floor_rgb;
	int		*ceiling_rgb;
}t_map;

/*-------------get_next_line-------------*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*my_filter_cut(char *save);
char	*my_filter(char *save);
int		my_strchr(char *str, char c);
char	*my_strjoin(char *save, char *bufer);
int		my_strlen(char *str);
/*-------------get_next_line-------------*/
/*-----split-----*/
char	**my_split(char const *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**original_split(char const *s, char c);
/*-----split-----*/

int		read_and_check(t_map *map);
void	*ft_calloc(int count, int size);
/*---------------------------parsing---------------------------------*/
/*---------------------------parsing---------------------------------*/
#endif