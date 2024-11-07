/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:44:23 by fgori             #+#    #+#             */
/*   Updated: 2024/11/07 19:12:50 by aosmenaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_mov(double angle, t_cube cube)
{
	double	ray_y;
	double	ray_x;

	ray_x = cube.player.pos.x + cos(angle) * 20;
	ray_y = cube.player.pos.y + sin(angle) * 20;
	if (!check_collision(ray_x, ray_y, cube.map.map))
		return (1);
	else
		return (0);
}

int	check_distance(t_cube cube, char direction)
{
	float	angle;

	if (direction == 'a')
		angle = cube.player.angle - (90 * M_PI / 180);
	else if (direction == 'd')
		angle = cube.player.angle + (90 * M_PI / 180);
	else if (direction == 's')
		angle = cube.player.angle + (180 * M_PI / 180);
	else
		angle = cube.player.angle;
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
	{
		angle -= 2 * M_PI;
	}
	return (check_mov(angle, cube));
}

static void	handle_angle(t_cube *cube)
{
	double	rot_step;

	rot_step = 0.07;
	if (cube->input.left)
		cube->player.angle -= rot_step;
	if (cube->input.right)
		cube->player.angle += rot_step;
	if (cube->player.angle < 0)
		cube->player.angle += 2 * M_PI;
	if (cube->player.angle > 2 * M_PI)
		cube->player.angle -= 2 * M_PI;
}

static void	exec_movement(t_cube *cube, double new_x, double new_y)
{
	if (check_collision(new_x, new_y, cube->map.map))
	{
		cube->player.pos.x = new_x;
		cube->player.pos.y = new_y;
	}
}

int	handle_movement(t_cube *cube)
{
	double	move_step;

	move_step = 20;
	if (cube->input.w && !check_distance(*cube, 'w'))
		exec_movement(cube, cube->player.pos.x + cos(cube->player.angle)
			* move_step, cube->player.pos.y + sin(cube->player.angle)
			* move_step);
	if (cube->input.s && !check_distance(*cube, 's'))
		exec_movement(cube, cube->player.pos.x - cos(cube->player.angle)
			* move_step, cube->player.pos.y - sin(cube->player.angle)
			* move_step);
	if (cube->input.a && !check_distance(*cube, 'a'))
		exec_movement(cube, cube->player.pos.x - cos(cube->player.angle + (90
					* M_PI / 180)) * move_step, cube->player.pos.y
			- sin(cube->player.angle + (90 * M_PI / 180)) * move_step);
	if (cube->input.d && !check_distance(*cube, 'd'))
		exec_movement(cube, cube->player.pos.x - cos(cube->player.angle - (90
					* M_PI / 180)) * move_step, cube->player.pos.y
			- sin(cube->player.angle - (90 * M_PI / 180)) * move_step);
	handle_angle(cube);
	return (0);
}
