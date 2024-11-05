/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:45:57 by aosmenaj          #+#    #+#             */
/*   Updated: 2024/11/05 16:49:37 by aosmenaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

void	ray_init(t_ray *ray, t_cube *cube)
{
	ray->id_ray = 0;
	ray->num_rays = cube->win.win_width;
	ray->FOV = 60 * (M_PI / 180);
	ray->angle_step = ray->FOV / ray->num_rays;
	ray->ray_angle = cube->player.angle - (ray->FOV / 2);
	if (ray->ray_angle < 0)
		ray->ray_angle += 2 * M_PI;
	if (ray->ray_angle > 2 * M_PI)
		ray->ray_angle -= 2 * M_PI;
}

void	ray_calc_init(t_ray *ray, t_cube *cube)
{
	ray->hit = 0;
	ray->posX = cube->player.pos.x;
	ray->posY = cube->player.pos.y;
	ray->rayDirx = cos(ray->ray_angle);
	ray->rayDiry = sin(ray->ray_angle);
	ray->mapx = (int)(ray->posX);
	ray->mapy = (int)(ray->posY);
	ray->delta_dist_x = fabs(1 / ray->rayDirx);
	ray->delta_dist_y = fabs(1 / ray->rayDiry);
}

void	ray_calc_step_sidedist(t_ray *ray)
{
	if (ray->rayDirx < 0)
	{
		ray->stepX = -1;
		ray->side_dist_x = (ray->posX - ray->mapx) * ray->delta_dist_x;
	}
	else
	{
		ray->stepX = 1;
		ray->side_dist_x = ((ray->mapx + 1.0) - ray->posX) * ray->delta_dist_x;
	}
	if (ray->rayDiry < 0)
	{
		ray->stepY = -1;
		ray->side_dist_y = (ray->posY - ray->mapy) * ray->delta_dist_y;
	}
	else
	{
		ray->stepY = 1;
		ray->side_dist_y = ((ray->mapy + 1.0) - ray->posY) * ray->delta_dist_y;
	}
}

void	determine_hit(t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->hitx = ray->posX + ray->side_dist_x * ray->rayDirx;
		ray->hity = ray->posY + ray->side_dist_x * ray->rayDiry;
	}
	else
	{
		ray->hitx = ray->posX + ray->side_dist_y * ray->rayDirx;
		ray->hity = ray->posY + ray->side_dist_y * ray->rayDiry;
	}
	if (ray->side == 0)
		ray->ray_length = (ray->mapx - ray->posX + (1 - ray->stepX) / 2)
			/ ray->rayDirx;
	else
		ray->ray_length = (ray->mapy - ray->posY + (1 - ray->stepY) / 2)
			/ ray->rayDiry;
}

void	find_wall(t_ray *ray, t_cube *cube)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->mapx += ray->stepX;
			ray->side = 0;
			cube->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->mapy += ray->stepY;
			ray->side = 1;
			cube->side = 1;
		}
		if (wallloak(ray->mapx, ray->mapy, cube->map.map))
			ray->hit = 1;
	}
}
