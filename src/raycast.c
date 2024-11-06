/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:45:57 by aosmenaj          #+#    #+#             */
/*   Updated: 2024/11/06 12:25:34 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

void	ray_init(t_ray *ray, t_cube *cube)
{
	ray->id_ray = 0;
	ray->num_rays = cube->win.win_width;
	ray->fov = 60 * (M_PI / 180);
	ray->angle_step = ray->fov / ray->num_rays;
	ray->ray_angle = cube->player.angle - (ray->fov / 2);
	if (ray->ray_angle < 0)
		ray->ray_angle += 2 * M_PI;
	if (ray->ray_angle > 2 * M_PI)
		ray->ray_angle -= 2 * M_PI;
}

void	ray_calc_init(t_ray *ray, t_cube *cube)
{
	ray->hit = 0;
	ray->pos_x = cube->player.pos.x;
	ray->pos_y = cube->player.pos.y;
	ray->ray_dirx = cos(ray->ray_angle);
	ray->ray_diry = sin(ray->ray_angle);
	ray->mapx = (int)(ray->pos_x);
	ray->mapy = (int)(ray->pos_y);
	ray->delta_dist_x = fabs(1 / ray->ray_dirx);
	ray->delta_dist_y = fabs(1 / ray->ray_diry);
}

void	ray_calc_step_sidedist(t_ray *ray)
{
	if (ray->ray_dirx < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->mapx) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((ray->mapx + 1.0) - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_diry < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->mapy) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((ray->mapy + 1.0) - ray->pos_y) * ray->delta_dist_y;
	}
}

void	determine_hit(t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->hitx = ray->pos_x + ray->side_dist_x * ray->ray_dirx;
		ray->hity = ray->pos_y + ray->side_dist_x * ray->ray_diry;
	}
	else
	{
		ray->hitx = ray->pos_x + ray->side_dist_y * ray->ray_dirx;
		ray->hity = ray->pos_y + ray->side_dist_y * ray->ray_diry;
	}
	if (ray->side == 0)
		ray->ray_length = (ray->mapx - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dirx;
	else
		ray->ray_length = (ray->mapy - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_diry;
}

void	find_wall(t_ray *ray, t_cube *cube)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->mapx += ray->step_x;
			ray->side = 0;
			cube->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->mapy += ray->step_y;
			ray->side = 1;
			cube->side = 1;
		}
		if (wallloak(ray->mapx, ray->mapy, cube->map.map))
			ray->hit = 1;
	}
}
