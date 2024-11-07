/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:00:32 by fgori             #+#    #+#             */
/*   Updated: 2024/11/07 19:22:57 by aosmenaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	decide_tex_direc(t_wall *new, t_cube *cube)
{
	if (cube->side == 0 && cos(new->angle) < 0)
	{
		new->text = cube->text.we;
		new->direction = 3;
	}
	else if (cube->side == 0)
	{
		new->text = cube->text.ea;
		new->direction = 1;
	}
	else if (cube->side == 1 && sin(new->angle) < 0)
	{
		new->text = cube->text.no;
		new->direction = 0;
	}
	else if (cube->side == 1)
	{
		new->text = cube->text.so;
		new->direction = 2;
	}
}

static void	take_wall(t_wall *new, t_cube *cube)
{
	int	x;
	int	y;

	decide_tex_direc(new, cube);
	y = ((int)new->cor.y) / 64;
	x = ((int)new->cor.x) / 64;
	if (y < 0)
		y = 0;
	if (y >= size_mtx('y', cube->map.map))
		y = size_mtx('y', cube->map.map) - 1;
	if (x < 0)
		x = 0;
	if (x >= size_mtx('x', cube->map.map))
		x = size_mtx('x', cube->map.map) - 1;
	if (cube->map.map[y][x] == 'D')
	{
		new->text = cube->text.door;
		new->is_door = true;
	}
}

t_wall	*ft_lstnew_cube(double lenght, t_pos *pos, double angle, t_cube *cube)
{
	t_wall	*new;
	double	new_angle;

	new = (void *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->angle = angle;
	new->cor.x = pos->x;
	new->cor.y = pos->y;
	new->is_door = false;
	new_angle = angle - cube->player.angle;
	if (new_angle < 0)
		new_angle += 2 * M_PI;
	if (new_angle > 2 * M_PI)
		new_angle -= 2 * M_PI;
	new->ray_lenght = lenght * cos(new_angle);
	take_wall(new, cube);
	new->wall_height = (int)((cube->win.win_height * 64) / new->ray_lenght);
	new->wall_top = (cube->win.win_height / 2) - (new->wall_height / 2);
	new->wall_bottom = (cube->win.win_height / 2) + (new->wall_height / 2);
	new->wall_width = 0;
	new->next = NULL;
	return (new);
}

void	correct_lst(t_wall *node)
{
	t_wall	*tmp;
	t_wall	*tmp_two;
	int		i;
	int		width;

	i = 0;
	tmp = node;
	tmp_two = node;
	while (tmp->next)
	{
		while (tmp_two->next && (int)tmp->cor.x == (int)tmp_two->cor.x)
		{
			tmp_two->idx = i;
			tmp_two = tmp_two->next;
			i++;
		}
		tmp_two->idx = i;
		width = (int)(tmp_two->idx - tmp->idx) - 1;
		while (tmp->idx < tmp_two->idx)
		{
			tmp->wall_width = width;
			tmp = tmp->next;
		}
	}
	return ;
}

void	ft_lstclear_cube(t_wall **lst)
{
	t_wall	*temp;

	if (!lst)
	{
		lst = NULL;
		return ;
	}
	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
}
