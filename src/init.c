/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:39:36 by fgori             #+#    #+#             */
/*   Updated: 2024/11/06 12:29:09 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	cube_init2(t_cube *cube)
{
	cube->text.no = NULL;
	cube->text.so = NULL;
	cube->text.ea = NULL;
	cube->text.we = NULL;
	cube->text.c = -1;
	cube->text.f = -1;
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
	cube_init2(cube);
}
