/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:16:17 by fgori             #+#    #+#             */
/*   Updated: 2024/10/11 11:34:58 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	display_map(t_cube *cube)
{
	int	x;
	int	y;

	x = (cube->win.win_width / 3) * 2;
	y = (cube->win.win_height / 3) * 2;
	if (cube->map.level == 0)
		return;
	else
	{
		while (x < cube->win.win_width)
		{
			y = (cube->win.win_height / 3) * 2;
			while (y < cube->win.win_height)
			{
				mlx_pixel_put(cube->win.mlx_ptr, cube->win.win_ptr, x, y, 0xc0c0c0);
				y++;
			}
			x++;
		}
	}
}
