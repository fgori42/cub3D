/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:09 by fgori             #+#    #+#             */
/*   Updated: 2024/11/06 12:15:33 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

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
	return (0);
}

int	main(int ac, char *ag[])
{
	t_cube	cube;

	cube_init(&cube);
	if (ac != 2)
	{
		perror("ERROR\ninvalid argument");
		exit(1);
	}
	cube.win.mlx_ptr = mlx_init();
	if (parsing(&cube, ag[1]) == 1)
	{
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
