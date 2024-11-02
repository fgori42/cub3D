/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:58:45 by fgori             #+#    #+#             */
/*   Updated: 2024/11/01 22:08:19 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	print_wall_in_img(t_wall *tmp, t_cube *cube, t_pos *utils, t_img *new_img)
{
	if (utils->y < 0)
			utils->y = 0;
	if (tmp->wall_bottom >= cube->win.win_height)
		tmp->wall_bottom = cube->win.win_height;
	while ( utils->y < tmp->wall_bottom)
	{
		if (tmp->idx == 900)
		{
			if (cube->map.map[(int)tmp->cor.y / 64][(int)tmp->cor.x / 64] == 'D')
			{
				cube->input.dor.x = (int)tmp->cor.x / 64;
				cube->input.dor.y = (int)tmp->cor.y / 64;
				cube->input.is_door = true;
			}
			else
			{
				cube->input.is_door = false;
			}
		}
		int texture_y = (utils->y - tmp->wall_top) * cube->texture.height / tmp->wall_height;
		if (texture_y >= cube->texture.height)
			texture_y = cube->texture.height - 1;
		// Get the color from the texture
		int color = get_texture_color(tmp->text, cube->texture.width, cube->texture.height, utils->x, texture_y);
		
			img_pixel_put(color, tmp->idx, utils->y, &new_img);
		
		utils->y++;
	}
}

void	print_world(t_wall *tmp, t_cube *cube)
{
	int		y1;
	t_pos	utils;
	t_img	*new_img;
	t_wall	*tmp_two;
	
	new_img = ft_calloc(1, sizeof(t_img));
	new_img->image = mlx_new_image(cube->win.mlx_ptr, cube->win.win_width, cube->win.win_height);
	new_img->data = mlx_get_data_addr(new_img->image, &new_img->bpp, &new_img->size_line, &new_img->format);
	cube->img = new_img;
	while (tmp->next)
	{
		tmp_two = cube->inst;
		y1 = 0;
		if (hit_vertical(tmp))
    		utils.x = ((int)tmp->cor.y % 64);
		else
			utils.x = ((int)tmp->cor.x % 64);
		while (y1 < tmp->wall_top && tmp->wall_top <= cube->win.win_height)
		{
			img_pixel_put(cube->text.C, tmp->idx, y1, &new_img);
			y1++;
		}
		y1 = tmp->wall_bottom - 1;
		while (y1 < cube->win.win_height && tmp->wall_bottom > 0)
		{
			img_pixel_put(cube->text.F, tmp->idx, y1, &new_img);
			y1++;
		}
		utils.y = tmp->wall_top;
		print_wall_in_img(tmp, cube, &utils, new_img);
		tmp = tmp->next;
		cube->inst = tmp;
		free(tmp_two);
	}
	draw_animation(cube);
	display_map(cube);
	mlx_put_image_to_window(cube->win.mlx_ptr, cube->win.win_ptr, new_img->image, 0, 0);
	mlx_destroy_image(cube->win.mlx_ptr, new_img->image);
	free(new_img);
}
