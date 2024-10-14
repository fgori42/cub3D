/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:00:32 by fgori             #+#    #+#             */
/*   Updated: 2024/10/14 15:00:42 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_wall	*ft_lstnew_cube(double lenght, t_pos *pos, double angle, t_cube *cube )
{
	t_wall	*new;
	double	new_angle;
	//int map_size = size_mtx('x', cube->map.map) * size_mtx('y', cube->map.map);
	
	new = (void *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->angle = angle;
	new->x = pos->x;
	new->y = pos->y;
	new_angle = angle - cube->player.angle;
	if (new_angle < 0)
		new_angle += 2 * M_PI;
	if (new_angle > 2 * M_PI)
		new_angle -= 2 * M_PI;
	new->ray_lenght = lenght * cos(new_angle);
    new->wall_height = (int)((cube->win.win_height * 64) / new->ray_lenght); // Altezza del muro corretta
	//if (new->wall_height > cube->win.win_height)
	//	new->wall_height = cube->win.win_height;
	new->wall_top = (cube->win.win_height / 2) - (new->wall_height / 2);
	new->wall_bottom = (cube->win.win_height / 2) + (new->wall_height / 2);
	new->wall_width = 0;
	new->next = NULL;
	return (new);
}

t_wall	*ft_lstlast_cube(t_wall *lst)
{
	while (lst && lst-> next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_cube(t_wall **lst, t_wall *new)
{
	t_wall	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	temp = ft_lstlast_cube(*lst);
	temp->next = new;
}

void	correct_lst(t_wall *node)
{
	t_wall	*tmp;
	t_wall	*tmp_two;
	int		i;
	int		width;

	if (!node->next)
		return ;
	i = 0;
	tmp = node;
	tmp_two = node;
	while (tmp->next)
	{
		while (tmp_two->next && (int)tmp->x == (int)tmp_two->x)
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
}
