/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:16:17 by fgori             #+#    #+#             */
/*   Updated: 2024/10/21 12:26:44 by fgori            ###   ########.fr       */
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
			color = get_texture_color(src->image, 500, 300, x, y);
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

void	put_mini(t_cube *cube, t_img mini)
{
	
}

void	display_map(t_cube *cube)
{
	int	x;
	int	y;
	int	i;
	t_img	*minimap;

	x = 0;
	y = 0;
	i = 0;
	if (cube->map.level == 0)
		return;
	else
	{
		minimap = ft_calloc(1, sizeof(t_img));
		minimap->image = mlx_new_image(cube->win.mlx_ptr, cube->minimap.mini_wid, cube->minimap.mini_height);
		minimap->data = mlx_get_data_addr(minimap->image, &minimap->bpp, &minimap->size_line, &minimap->format);
		while (x < cube->minimap.mini_wid)
		{
			y = 0;
			while (y <  cube->minimap.mini_height)
			{
				if ((cube->map.level == 1 && i % 2 == 0) || cube->map.level == 2)
					img_pixel_put(16711680, x, y, &minimap);
				y++;
				i++;
			}
			i++;
			x++;
		}
		//mlx_put_image_to_window(cube->win.mlx_ptr, cube->win.win_ptr, minimap->image, 500, 300);
		plus_img(minimap, cube->minimap.mini_start_x, cube->minimap.mini_start_y, cube);
		//mlx_do_sync(cube->win.mlx_ptr);
		mlx_destroy_image(cube->win.mlx_ptr, minimap->image);
		free(minimap);
	}
}
