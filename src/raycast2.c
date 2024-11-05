/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:50:12 by aosmenaj          #+#    #+#             */
/*   Updated: 2024/11/05 17:16:21 by aosmenaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calculate_ray(t_cube *cube)
{
	t_ray	ray;
	t_wall	*tmp;
	t_pos	pos;

	ray_init(&ray, cube);
	while (ray.id_ray < ray.num_rays)
	{
		ray_calc_init(&ray, cube);
		ray_calc_step_sidedist(&ray);
		find_wall(&ray, cube);
		determine_hit(&ray);
		pos.x = ray.hitx;
		pos.y = ray.hity;
		tmp = ft_lstnew_cube(ray.ray_length, &pos, ray.ray_angle, cube);
		ft_lstadd_back_cube(&cube->inst, tmp);
		ray.ray_angle += ray.angle_step;
		if (ray.ray_angle < 0)
			ray.ray_angle += 2 * M_PI;
		if (ray.ray_angle > 2 * M_PI)
			ray.ray_angle -= 2 * M_PI;
		ray.id_ray++;
	}
	correct_lst(cube->inst);
	print_world(cube->inst, cube);
}
