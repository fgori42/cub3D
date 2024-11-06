/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_managemet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:14:49 by fgori             #+#    #+#             */
/*   Updated: 2024/11/06 12:29:59 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

short	wallloak(int x, int y, char **map)
{
	x /= 64;
	y /= 64;
	if (map[y][x] == 'D')
		return (2);
	if (map[y][x] == '1')
		return (1);
	return (0);
}

int	size_mtx(char size, char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (size == 'x')
	{
		while (map[y][x])
			x++;
		return (x);
	}
	if (size == 'y')
	{
		while (map[y])
			y++;
		return (y);
	}
	return (0);
}

static void	free_textur(t_cube *cube)
{
	if (cube->text.no)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.no);
	if (cube->text.ea != NULL)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.ea);
	if (cube->text.so)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.so);
	if (cube->text.we)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.we);
	if (cube->text.door)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.door);
}

int	on_destroy(t_cube *cube)
{
	if (cube->map.map)
		freeall(cube->map.map);
	if (cube->map.map_check)
		freeall(cube->map.map_check);
	free_textur(cube);
	if (cube->inst)
		ft_lstclear_cube(&cube->inst);
	if (cube->win.win_ptr)
		mlx_destroy_window(cube->win.mlx_ptr, cube->win.win_ptr);
	if (cube->win.mlx_ptr)
	{
		mlx_destroy_display(cube->win.mlx_ptr);
		free(cube->win.mlx_ptr);
	}
	exit(0);
	return (0);
}

int	check_collision(double x, double y, char **map)
{
	double	player_size;

	player_size = 5;
	if (wallloak(x - player_size, y - player_size, map) || wallloak(x
			+ player_size, y - player_size, map) || wallloak(x - player_size, y
			+ player_size, map) || wallloak(x + player_size, y + player_size,
			map))
	{
		return (0);
	}
	return (1);
}
