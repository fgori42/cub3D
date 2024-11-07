/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:25:13 by fgori             #+#    #+#             */
/*   Updated: 2024/11/07 14:03:06 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	make_angle(char **map, t_cube *cube, int x, int y)
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
	cube->map.map[y][x] = '0';
}

bool	map_check(t_cube *cube, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!cube->player.existence && (map[y][x] == 'N' || map[y][x] == 'S'
					|| map[y][x] == 'W' || map[y][x] == 'E'))
			{
				cube->player.pos.x = x * 64 + 32;
				cube->player.pos.y = y * 64 + 32;
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

static int	full_fil(int x, int y, char **map)
{
	int	i;

	i = 0;
	if (x < 0 || x >= (int)ft_strlen(map[y])
		|| y < 0 || y >= size_mtx('y', map))
		return (1);
	if (map[y][x] == '1')
		return (0);
	else if (x == 0 || y == 0 || x == (int)ft_strlen(map[y])
		|| y == size_mtx('y', map) - 1 || map[y][x] == '\0' || map[y][x] == ' ')
		return (1);
	else if (map[y][x] != '0' && map[y][x] != ' ' && map[y][x] != 'D'
		&& map[y][x] != '1')
		return (-1);
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
	int	ret;

	y = 0;
	ret = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '1' && map[y][x] != ' ')
				ret += full_fil(x, y, map);
			x++;
		}
		y++;
	}
	if (ret > 0)
		return (put_error("map not protected by wall", NULL, 1));
	if (ret < 0)
		return (put_error("strange char", NULL, 1));
	return (0);
}

bool	is_missing(t_cube *cube)
{
	if (!cube->text.door || !cube->text.ea || !cube->text.no || !cube->text.so
		|| !cube->text.we || cube->text.f == -1 || cube->text.c == -1)
		return (false);
	return (true);
}
