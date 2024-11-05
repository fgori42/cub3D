/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:39:36 by aosmenaj          #+#    #+#             */
/*   Updated: 2024/11/05 15:39:54 by aosmenaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_image(t_img *bg, t_img *img, int start_x, int start_y)
{
	int	y;
	int	x;
	int	bg_x;
	int	bg_y;
	int	gun_pixel;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			bg_x = start_x + x;
			bg_y = start_y + y;
			gun_pixel = get_texture_color(img->image, x, y);
			if (gun_pixel != 0x00FFFFFF)
				img_pixel_put(gun_pixel, bg_x, bg_y, &bg);
			x++;
		}
		y++;
	}
}

void	take_frame(t_cube *cube, char *path_image, t_img *bg)
{
	t_img	*img;
	int		start_x;
	int		start_y;

	img = ft_calloc(1, sizeof(t_img));
	img->image = mlx_xpm_file_to_image(cube->win.mlx_ptr, path_image,
			&img->width, &img->height);
	start_x = cube->win.win_width - img->width;
	start_y = cube->win.win_height - img->height;
	draw_image(bg, img, start_x, start_y);
	mlx_destroy_image(cube->win.mlx_ptr, img->image);
	free(img);
}

void	decide_frame(t_cube *cube, int *time, char *frames[5])
{
	if (*time >= 0 && *time < 2)
		take_frame(cube, frames[1], cube->img);
	else if (*time >= 2 && *time < 4)
		take_frame(cube, frames[2], cube->img);
	else if (*time >= 4 && *time < 6)
		take_frame(cube, frames[3], cube->img);
	else if (*time >= 6 && *time < 8)
		take_frame(cube, frames[4], cube->img);
	else if (*time >= 8)
	{
		take_frame(cube, frames[0], cube->img);
		*time = 0;
		cube->input.f = false;
		if (cube->input.is_door)
			cube->map.map[(int)cube->input.dor.y][(int)cube->input.dor.x] = 'd';
		return ;
	}
}

void	draw_animation(t_cube *cube)
{
	static int	time;
	char		*frames[5];

	frames[0] = "./textures/gun1.xpm";
	frames[1] = "./textures/gun2.xpm";
	frames[2] = "./textures/gun3.xpm";
	frames[3] = "./textures/gun4.xpm";
	frames[4] = "./textures/gun5.xpm";
	if (cube->input.f == false)
		take_frame(cube, frames[0], cube->img);
	else
	{
		decide_frame(cube, &time, frames);
		time++;
	}
}
