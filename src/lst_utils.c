/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:00:32 by fgori             #+#    #+#             */
/*   Updated: 2024/10/16 14:13:42 by aosmenaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	take_wall(t_wall *new, t_cube *cube)
{
	double epsilon = 0.0000001;

    if (fabs(new->x - (int)new->x) < epsilon)
    {
        // Hit close to a vertical wall
        if (cos(new->angle) < 0)
        {
            // Hit on the west side
            new->text = cube->text.WE;
            new->direction = 3;
        }
        else
        {
            // Hit on the east side
            new->text = cube->text.EA;
            new->direction = 1;
        }
    }
    else if (fabs(new->y - (int)new->y) < epsilon)
    {
        // Hit close to a horizontal wall
        if (sin(new->angle) < 0)
        {
            // Hit on the north side
            new->text = cube->text.NO;
            new->direction = 0;
        }
        else
        {
            // Hit on the south side
            new->text = cube->text.SO;
            new->direction = 2;
        }
    }
}

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
	take_wall(new, cube);
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
