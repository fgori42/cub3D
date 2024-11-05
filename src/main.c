/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:09 by fgori             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/05 15:14:47 by aosmenaj         ###   ########.fr       */
=======
/*   Updated: 2024/11/05 12:51:07 by fgori            ###   ########.fr       */
>>>>>>> d1f98403e0897d2385103250fb9b80bf65912909
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

short	wallloak(int x, int y, char **map)
{
	x /= 64;
	y /= 64;
	if (map[y][x] == 'D')
		return (2);
	if (map[y][x] == '1')
		return (1);
	return (0);
}

int	size_mtx(char size, char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (size == 'x')
	{
		while (map[y][x])
			x++;
		return (x);
	}
	if (size == 'y')
	{
		while (map[y])
			y++;
		return (y);
	}
	return (0);
}

int	dtermine_color_endian(t_img image, int pixel_offset)
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

void	free_textur(t_cube *cube)
{
	if (cube->text.NO)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.NO);
	if (cube->text.EA != NULL)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.EA);
	if (cube->text.SO)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.SO);
	if (cube->text.WE)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.WE);
	if (cube->text.door)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.door);
}

int	on_destroy(t_cube *cube)
{
	if (cube->map.map)
		freeall(cube->map.map);
	if (cube->map.map_check)
		freeall(cube->map.map_check);
	free_textur(cube);
	if (cube->inst)
		ft_lstclear_cube(&cube->inst);
	if (cube->win.win_ptr)
		mlx_destroy_window(cube->win.mlx_ptr, cube->win.win_ptr);
	if (cube->win.mlx_ptr)
	{
		mlx_destroy_display(cube->win.mlx_ptr);
		free(cube->win.mlx_ptr);
	}
	exit(0);
	return (0);
}

void	door_open(t_cube *cube)
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

void	hold_door_minimap(int keysym, t_cube *cube)
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

int	check_collision(double x, double y, char **map)
{
	double	player_size;

	player_size = 5;
	if (wallloak(x - player_size, y - player_size, map) || wallloak(x
			+ player_size, y - player_size, map) || wallloak(x - player_size, y
			+ player_size, map) || wallloak(x + player_size, y + player_size,
			map))
	{
		return (0);
	}
	return (1);
}

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

void	exec_movement(t_cube *cube, double new_x, double new_y)
{
	if (check_collision(new_x, new_y, cube->map.map))
	{
		cube->player.pos.x = new_x;
		cube->player.pos.y = new_y;
	}
}

void	handle_angle(t_cube *cube)
{
	double	rot_step;

	rot_step = 0.08;
	if (cube->input.left)
		cube->player.angle -= rot_step;
	if (cube->input.right)
		cube->player.angle += rot_step;
	if (cube->player.angle < 0)
		cube->player.angle += 2 * M_PI;
	if (cube->player.angle > 2 * M_PI)
		cube->player.angle -= 2 * M_PI;
}

int	handle_movement(t_cube *cube)
{
	double	move_step;

	move_step = 10;
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

int	game_loop(t_cube *cube)
{
	handle_movement(cube);
	calculate_ray(cube);
	return (0);
}

int	handle_mouse_move(int x, int y, t_cube *cube)
{
	double	rot_step;
	int		center_x;
	int		center_y;

	(void)y;
	rot_step = 0.05;
	center_x = cube->win.win_width / 2;
	center_y = cube->win.win_height / 2;
	if (x != center_x && !cube->input.c)
	{
		if (x > cube->prev_mouse_x)
			cube->player.angle += rot_step;
		else if (x < cube->prev_mouse_x)
			cube->player.angle -= rot_step;
		if (cube->player.angle < 0)
			cube->player.angle += 2 * M_PI;
		if (cube->player.angle > 2 * M_PI)
			cube->player.angle -= 2 * M_PI;
		mlx_mouse_move(cube->win.mlx_ptr, cube->win.win_ptr, center_x,
			center_y);
		cube->prev_mouse_x = center_x;
	}
	if (cube->input.c)
		mlx_mouse_show(cube->win.mlx_ptr, cube->win.win_ptr);
	return (0);
}

void	cube_init(t_cube *cube)
{
	cube->input.w = false;
	cube->input.a = false;
	cube->input.s = false;
	cube->input.d = false;
	cube->input.f = false;
	cube->input.c = false;
	cube->input.is_door = false;
	cube->player.existence = 0;
	cube->prev_mouse_x = 400;
	cube->input.left = false;
	cube->input.right = false;
	cube->win.mlx_ptr = NULL;
	cube->win.win_ptr = NULL;
	cube->map.map = NULL;
	cube->map.map_check = NULL;
	cube->map.size = NULL;
}

void	cube_init2(t_cube *cube)
{
	cube->text.NO = NULL;
	cube->text.SO = NULL;
	cube->text.EA = NULL;
	cube->text.WE = NULL;
	cube->text.C = -1;
	cube->text.F = -1;
	cube->text.door = NULL;
	cube->win.win_width = 1600;
	cube->win.win_height = 900;
	cube->minimap.mini_height = 0;
	cube->minimap.mini_wid = 0;
	cube->minimap.mini_start_x = 0;
	cube->minimap.mini_start_y = 0;
	cube->map.level = 0;
	cube->inst = NULL;
}

int	main(int ac, char *ag[])
{
	t_cube	cube;

	cube_init(&cube);
	cube_init2(&cube);
	if (ac != 2)
	{
		perror("ERROR\ninvalid argument");
		exit(1);
	}
	cube.win.mlx_ptr = mlx_init();
	if (parsing(&cube, ag[1]) == 1)
	{
		perror("bad parsing\n");
		on_destroy(&cube);
	}
	cube.win.win_ptr = mlx_new_window(cube.win.mlx_ptr, cube.win.win_width,
			cube.win.win_height, "PROVA");
	mlx_hook(cube.win.win_ptr, KeyPress, KeyPressMask, &on_keypress, &cube);
	mlx_hook(cube.win.win_ptr, KeyRelease, KeyReleaseMask, &on_keyrelease,
		&cube);
	mlx_hook(cube.win.win_ptr, 6, 1L << 6, handle_mouse_move, &cube);
	mlx_hook(cube.win.win_ptr, 33, 1L << 5, &on_destroy, &cube);
	mlx_loop_hook(cube.win.mlx_ptr, &game_loop, &cube);
	mlx_loop(cube.win.mlx_ptr);
	return (0);
}
