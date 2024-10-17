/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:47:00 by fgori             #+#    #+#             */
/*   Updated: 2024/10/16 15:30:59 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	put_error(char *str, char *str_two, int i)
{
	write(2, "ERROR\n", 6);
	write(2, str, ft_strlen(str));
	if (str_two)
		write(2, str_two, ft_strlen(str_two));
	return (i);
}

bool	is_cub(char *str)
{
	char	*tmp;

	tmp = ft_substr(str, ft_strlen(str) - 4, 4);
	if (ft_strncmp(tmp, ".cub", 4) == 0)
	{
		free(tmp);
		return (true);
	}
	else
	{
		free(tmp);
		return (false);
	}
}


char *gnl(char *str)
{
	int 	fd;
	int		control;
	char	*buff;
	char 	*txt;
	char	*sup;
	
	control = 1;
	buff = ft_calloc(2,1);
	txt = ft_calloc(1,1);
	fd = open(str,  O_RDWR );
	if (fd < 0)
		return (NULL);
	while (control > 0)
	{
		control = read(fd, buff, 1);
		sup = txt;
		txt = ft_strjoin(txt, buff);
		free(sup);
	}
	free(buff);
	return(txt);
}

int create_rgb(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**sup;

	sup = ft_split(str, ',');
	if (!sup)
		return (-1);
	r = ft_atoi(sup[0]);
	g = ft_atoi(sup[1]);
	b = ft_atoi(sup[2]);
	if (ft_strlen(sup[0]) > 3 || ft_strlen(sup[1]) > 3 || ft_strlen(sup[2]) > 3 ||
		r < 0 || r > 255 || g < 0 || g > 255 || b < 0 ||  b > 255 )
		return (-1);
	free(str);
	free(sup);
    return (r << 16 | g << 8 | b);
}

int	convert_rgb(char *str, t_text *home)
{
	int	j;
	
	j = 0;
	if (home->C == -1 && !ft_strncmp(str, "C", 1))
	{
		j = create_rgb(ft_strtrim(str, "C "));
		if (j == -1)
			return (-1);
		home->C = j;
	}
	else if (home->F == -1 && !ft_strncmp(str, "F", 1))
	{
		j = create_rgb(ft_strtrim(str, "F "));
		if (j == -1)
			return (-1);
		home->F = j;
	}
	else
		return (-1);
	return (0);
	
}

int	put_textur(char *str, t_text *home, t_cube *cube)
{
	char *sup;

	sup = ft_strchr(str, '.');
	if (sup)
	{
		if (!home->NO && ft_strncmp(str, "NO", 2) == 0 )
			home->NO = mlx_xpm_file_to_image(cube->win.mlx_ptr, sup, &cube->texture.width, &cube->texture.height);
		else if (!home->SO && ft_strncmp(str, "SO", 2) == 0 )
			home->SO = mlx_xpm_file_to_image(cube->win.mlx_ptr, sup, &cube->texture.width, &cube->texture.height);
		else if (!home->EA && ft_strncmp(str, "EA", 2) == 0 )
			home->EA = mlx_xpm_file_to_image(cube->win.mlx_ptr, sup, &cube->texture.width, &cube->texture.height);
		else if (!home->WE && ft_strncmp(str, "WE", 2) == 0 )
			home->WE = mlx_xpm_file_to_image(cube->win.mlx_ptr, sup, &cube->texture.width, &cube->texture.height);
		else
			return (put_error("textur not found: ", str, 1));
	}
	else
	{
		if (convert_rgb(str, home) == -1)
			return (put_error("color not found: ", str, 1));
	}
	return (0);
}

int	mtx_trim(t_map	*map, char **mtx, int start)
{
	int		len;
	int		i;
	char	**newMtx;

	i = 0;
	len = size_mtx('y', mtx) - start;
	newMtx = ft_calloc(len + 1, sizeof(char *));
	if (!newMtx)
		return (1);
	while (i < len)
	{
		newMtx[i] = ft_strdup(mtx[start]);
		start++;
		i++;
	}
	map->map = newMtx;
	i = 0;
	map->map_check = ft_calloc(size_mtx('y', newMtx) + 1, sizeof(char *));
	while(map->map[i])
	{
		map->map_check[i] = ft_strdup(map->map[i]);
		i++;
	}
	free(mtx);
	return (0);
}

bool	take_textur(t_cube *cube, char **text)
{
	int 	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(text[i], "NO", 2) == 0 || ft_strncmp(text[i], "SO", 2) == 0
			|| ft_strncmp(text[i], "WE", 2) == 0 || ft_strncmp(text[i], "EA", 2) == 0
			|| ft_strncmp(text[i], "C", 1) == 0 || ft_strncmp(text[i], "F", 1) == 0) 
			{
			if (put_textur(text[i], &cube->text, cube) == 1)
				return (false);
			}
		else
			return (false);
		i++;
	}
	if (mtx_trim(&cube->map, text,i) == 1)
		return (perror("Error\nimpossible to trim mtx"), false);
	return (true);
}
 
int	full_fil(int x, int y, char **map)
{
	int i;

	i = 0;
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == ' ' || x == 0 || y == 0 || x == (int)ft_strlen(map[y])
		|| y == size_mtx('y', map) || x > (int)ft_strlen(map[y + 1]) || x > (int)ft_strlen(map[y - 1]))
		return (1);
	else
	{
		map[y][x] = '1';
		i += full_fil(x + 1, y, map);
		i += full_fil(x - 1, y, map);
		i += full_fil(x, y + 1, map);
		i += full_fil(x, y - 1, map);
	}
	return (i);
}
 
int	map_fil(char **map)
{
	int	x;
	int	y;
	int ret;

	y = 0;
	ret = 0;
	while (map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != ' ' && map[y][x] != 'D' && map[y][x] != '1')
				return (put_error("strange char", "\n", 1));
			if (map[y][x] != '1' && map[y][x] != ' ')
				ret +=full_fil(x, y, map);
			x++;
		}
		y++;
	}
	if (ret > 0)
		return (put_error("map not protected by wall\n", NULL,1));
	return (0);
}

void	make_angle(char **map, t_cube *cube, int x, int y)
{
	if (map[y][x] == 'E')
		cube->player.angle = 0;
	if (map[y][x] == 'S')
		cube->player.angle = 90 * (M_PI / 180);
	if (map[y][x] == 'W')
		cube->player.angle = 180 * (M_PI / 180);
	if (map[y][x] == 'N')
		cube->player.angle = 270 * (M_PI / 180);
	map[y][x] = '0';
}

bool map_check(t_cube *cube, char **map)
{
	int	x;
	int y;

	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if (!cube->player.existence && (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W' || map[y][x] == 'E'))
			{
				cube->player.pos.x = x * 64;
				cube->player.pos.y = y * 64;
				make_angle(map, cube, x, y);
				cube->player.existence = true;
			}
			x++;
		}
		y++;
	}
	if (cube->player.existence == false)
		return (put_error("character not found", NULL, false));
	return (true);
}

int parsing(t_cube *cube, char *str)
{
	char	*mapFile;
	char	**openMap;

	if (!is_cub(str))
		return (1);

	mapFile = gnl(str);
	if (!mapFile)
		return (1);
	openMap = ft_split(mapFile, '\n');	
	free(mapFile);
	if (!take_textur(cube, openMap))
		return (1);
	if (!map_check(cube, cube->map.map_check))
		return(1);
	return (map_fil(cube->map.map_check));
}
