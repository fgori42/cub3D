/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:53:42 by fgori             #+#    #+#             */
/*   Updated: 2024/11/06 12:29:22 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	door_open(t_cube *cube)
{
	float	angle;
	double	ray_x;
	double	ray_y;
	int		x;
	int		y;

	angle = cube->player.angle;
	ray_x = cube->player.pos.x + cos(angle) * 60;
	ray_y = cube->player.pos.y + sin(angle) * 60;
	x = (int)ray_x / 64;
	y = (int)ray_y / 64;
	if (cube->map.map[y][x] == 'd')
		cube->map.map[y][x] = 'D';
	else if (cube->map.map[y][x] == 'D')
		cube->map.map[y][x] = 'd';
}

static void	hold_door_minimap(int keysym, t_cube *cube)
{
	if (keysym == XK_e)
		door_open(cube);
	if (keysym == XK_m)
	{
		cube->map.level++;
		if (cube->map.level > 2)
			cube->map.level = 0;
	}
}

int	on_keypress(int keysym, t_cube *cube)
{
	if (keysym == XK_W || keysym == XK_w)
		cube->input.w = true;
	else if (keysym == XK_A || keysym == XK_a)
		cube->input.a = true;
	else if (keysym == XK_S || keysym == XK_s)
		cube->input.s = true;
	else if (keysym == XK_D || keysym == XK_d)
		cube->input.d = true;
	if (keysym == XK_F || keysym == XK_f)
		cube->input.f = true;
	if (keysym == XK_c)
		cube->input.c = true;
	hold_door_minimap(keysym, cube);
	if (keysym == XK_Left)
		cube->input.left = true;
	if (keysym == XK_Right)
		cube->input.right = true;
	if (keysym == XK_Escape)
		on_destroy(cube);
	return (0);
}

int	on_keyrelease(int keysym, t_cube *cube)
{
	if (keysym == XK_W || keysym == XK_w)
		cube->input.w = false;
	if (keysym == XK_A || keysym == XK_a)
		cube->input.a = false;
	if (keysym == XK_S || keysym == XK_s)
		cube->input.s = false;
	if (keysym == XK_D || keysym == XK_d)
		cube->input.d = false;
	if (keysym == XK_c)
		cube->input.c = false;
	if (keysym == XK_Left)
		cube->input.left = false;
	if (keysym == XK_Right)
		cube->input.right = false;
	return (0);
}
