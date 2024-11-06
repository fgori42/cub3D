/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:01:55 by fgori             #+#    #+#             */
/*   Updated: 2024/11/06 12:09:11 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	dtermine_color_endian(t_img image, int pixel_offset)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				color;

	r = image.data[pixel_offset];
	g = image.data[pixel_offset + 1];
	b = image.data[pixel_offset + 2];
	color = (r << 16) | (g << 8) | b;
	return (color);
}

int	get_texture_color(void *img, int tex_x, int tex_y)
{
	t_img	image;
	int		color;
	int		endian;
	int		pixel_offset;

	if (tex_x < 0)
		tex_x = 0;
	image.data = mlx_get_data_addr(img, &image.bpp, &image.size_line, &endian);
	pixel_offset = tex_y * image.size_line + tex_x * (image.bpp / 8);
	if (endian == 0)
		color = *(int *)(image.data + pixel_offset);
	else
		color = dtermine_color_endian(image, pixel_offset);
	color = *(int *)(image.data + pixel_offset);
	return (color);
}

void	img_pixel_put(int color, int x, int y, t_img **img)
{
	char	*pixel;

	if (y < 0 || y > 900)
		return ;
	if (x < 0 || x > 1600)
		return ;
	pixel = (*img)->data + ((y * (*img)->size_line) + (x * (*img)->bpp / 8));
	*(int *)pixel = color;
}
