/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:16:17 by fgori             #+#    #+#             */
/*   Updated: 2024/11/07 19:25:49 by aosmenaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	plus_img(t_img *src, int startX, int startY, t_cube *cube)
{
	int		color;
	char	*pixel_dest;
	t_pos	cor;
	int		orig_starty;

	orig_starty = startY;
	cor.x = 0;
	while (cor.x < cube->minimap.mini_wid)
	{
		startY = orig_starty;
		cor.y = 0;
		while (cor.y++ < cube->minimap.mini_height)
		{
			color = get_texture_color(src->image, cor.x, cor.y);
			pixel_dest = (cube->img)->data + ((startY * (cube->img)->size_line)
					+ (startX * (cube->img)->bpp / 8));
			if (color != 0x00000000)
				*(int *)pixel_dest = color;
			startY++;
		}
		startX++;
		cor.x++;
	}
}

int	what_i_see(int x, int y, char **map)
{
	if (y < 0)
		y = 0;
	if (y >= size_mtx('y', map))
		y = size_mtx('y', map) - 1;
	if (x < 0)
		x = 0;
	if (x >= size_mtx('x', map))
		x = size_mtx('x', map) - 1;
	if (map[y][x] == '1')
		return (4210752);
	if (map[y][x] == '0')
		return (12632256);
	if (map[y][x] == 'D' || map[y][x] == 'd')
		return (13037520);
	if (map[y][x] == '\0')
		return (0);
	else
		return (16711680);
}

void	mini_pixel_put(t_cube *cube, int s_[2], int x[3], t_img *mini)
{
	if (s_[0] == (int)(cube->player.pos.x / 64)
		&& s_[1] == (int)(cube->player.pos.y / 64) && ((cube->map.level == 1
				&& x[2] % 2 == 0) || cube->map.level == 2))
		img_pixel_put(16776960, x[0], x[1], &mini);
	else if ((cube->map.level == 1 && x[2] % 2 == 0) || cube->map.level == 2)
		img_pixel_put(what_i_see(s_[0], s_[1], cube->map.map), x[0], x[1],
			&mini);
}

void	put_mini(t_cube *cube, t_img *mini)
{
	int	s_[2];
	int	x[3];

	x[0] = 0;
	x[1] = 0;
	x[2] = 0;
	s_[0] = (cube->player.pos.x / 64) - 3;
	while (x[0] < cube->minimap.mini_wid)
	{
		x[1] = 0;
		s_[1] = (cube->player.pos.y / 64) - 1;
		while (x[1] < cube->minimap.mini_height)
		{
			mini_pixel_put(cube, s_, x, mini);
			x[1]++;
			x[2]++;
			if (x[1] % 32 == 0)
				s_[1]++;
		}
		x[2]++;
		x[0]++;
		if (x[0] % 32 == 0)
			s_[0]++;
	}
}

void	display_map(t_cube *cube)
{
	t_img	*minimap;

	if (cube->map.level == 0)
		return ;
	else
	{
		cube->minimap.mini_height = size_mtx('y', cube->map.map) * 16;
		cube->minimap.mini_wid = size_mtx('x', cube->map.map) * 16 / 2;
		minimap = ft_calloc(1, sizeof(t_img));
		minimap->image = mlx_new_image(cube->win.mlx_ptr,
				cube->minimap.mini_wid, cube->minimap.mini_height);
		minimap->data = mlx_get_data_addr(minimap->image, &minimap->bpp,
				&minimap->size_line, &minimap->format);
		put_mini(cube, minimap);
		plus_img(minimap, cube->minimap.mini_start_x,
			cube->minimap.mini_start_y, cube);
		mlx_destroy_image(cube->win.mlx_ptr, minimap->image);
		free(minimap);
	}
}
