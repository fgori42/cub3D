/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:16:17 by fgori             #+#    #+#             */
/*   Updated: 2024/10/21 13:27:44 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	plus_img(t_img *src, int startX, int startY, t_cube *cube)
{
	int		color;
	char	*pixel_dest;
	int		y;
	int		x;
	int		orig_startY;

	orig_startY = startY;
	x = 0;
	while (x <  cube->minimap.mini_wid)
	{
		startY = orig_startY;
		y = 0;
		while (y++ <  cube->minimap.mini_height)
		{
			color = get_texture_color(src->image, cube->minimap.mini_wid, cube->minimap.mini_height, x, y);
			pixel_dest = (cube->img)->data + ((startY * (cube->img)->size_line) + (startX * (cube->img)->bpp / 8));
			if (color != 0x00000000)
			{
				*(int *)pixel_dest = color; 
			}
			startY++;
		}
		startX++;
		x++;
	}
}

int what_i_see(int x, int y, char **map)
{
	if (x < 0|| y < 0 || y >= size_mtx('y', map))
		return (0);
	if (map[y][x] == '1')
		return (4210752);
	if (map[y][x] == '0')
		return (12632256);
	if (map[y][x] == '\0')
		return (0);
	else
		return (16711680);
}

//void	put_cube(int color, t_img **mini, int startx, int starty)
//{
//	int	x;
//	int	y;

//	x = 0;
//	while ( x < 64)
//	{
//		y = 0;
//		while (y < 64)
//		{	
//		}
//	}
//}
//what_i_see(s_x, s_y, cube->map.map)
void	put_mini(t_cube *cube, t_img *mini)
{
	int	x;
	int	y;
	int	i;
	int s_x;
	int s_y;
	
	x = 0;
	y = 0;
	i = 0;
	s_x = (cube->player.pos.x /64) - 4;
		while (x < cube->minimap.mini_wid)
		{
			y = 0;
			s_y = (cube->player.pos.y /64) - 2;
			while (y <  cube->minimap.mini_height)
			{
				if (s_x == (int)(cube->player.pos.x /64) && s_y == (int)(cube->player.pos.y /64) && ((cube->map.level == 1 && i % 2 == 0) || cube->map.level == 2))
					img_pixel_put(16776960 , x, y, &mini);
				else if ((cube->map.level == 1 && i % 2 == 0) || cube->map.level == 2)
					img_pixel_put(what_i_see(s_x, s_y, cube->map.map) , x, y, &mini);
				y++;
				i++;
				if (y % 64 == 0)
					s_y++;
			}
			i++;
			x++;
			if (x % 64 == 0)
					s_x++;
		}
}

void	display_map(t_cube *cube)
{
	t_img	*minimap;

	if (cube->map.level == 0)
		return;
	else
	{
		minimap = ft_calloc(1, sizeof(t_img));
		minimap->image = mlx_new_image(cube->win.mlx_ptr, cube->minimap.mini_wid, cube->minimap.mini_height);
		minimap->data = mlx_get_data_addr(minimap->image, &minimap->bpp, &minimap->size_line, &minimap->format);
		put_mini(cube, minimap);
		//mlx_put_image_to_window(cube->win.mlx_ptr, cube->win.win_ptr, minimap->image, 500, 300);
		plus_img(minimap, cube->minimap.mini_start_x, cube->minimap.mini_start_y, cube);
		//mlx_do_sync(cube->win.mlx_ptr);
		mlx_destroy_image(cube->win.mlx_ptr, minimap->image);
		free(minimap);
	}
}
