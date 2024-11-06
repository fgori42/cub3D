/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:50:34 by fgori             #+#    #+#             */
/*   Updated: 2024/11/06 12:27:27 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	place_textur(char *str, char *sup, t_text *home, t_cube *cube)
{
	if (!home->no && ft_strncmp(str, "NO", 2) == 0)
		home->no = mlx_xpm_file_to_image(cube->win.mlx_ptr, sup,
				&cube->texture.width, &cube->texture.height);
	else if (!home->so && ft_strncmp(str, "SO", 2) == 0)
		home->so = mlx_xpm_file_to_image(cube->win.mlx_ptr, sup,
				&cube->texture.width, &cube->texture.height);
	else if (!home->ea && ft_strncmp(str, "EA", 2) == 0)
		home->ea = mlx_xpm_file_to_image(cube->win.mlx_ptr, sup,
				&cube->texture.width, &cube->texture.height);
	else if (!home->we && ft_strncmp(str, "WE", 2) == 0)
		home->we = mlx_xpm_file_to_image(cube->win.mlx_ptr, sup,
				&cube->texture.width, &cube->texture.height);
	else
		return (put_error("textur not found: ", str, 1));
	return (0);
}

static int	nbr_coma(char *str)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			x++;
		i++;
	}
	return (x);
}

static int	create_rgb(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**sup;

	sup = ft_split(str, ',');
	if (!sup || nbr_coma(str) != 2)
	{
		free(str);
		freeall(sup);
		return (-1);
	}
	r = ft_atoi(sup[0]);
	g = ft_atoi(sup[1]);
	b = ft_atoi(sup[2]);
	free(str);
	freeall(sup);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

static int	convert_rgb(char *str, t_text *home)
{
	int	j;

	j = 0;
	if (home->c == -1 && !ft_strncmp(str, "C", 1))
	{
		j = create_rgb(ft_strtrim(str, "C "));
		if (j == -1)
			return (-1);
		home->c = j;
	}
	else if (home->f == -1 && !ft_strncmp(str, "F", 1))
	{
		j = create_rgb(ft_strtrim(str, "F "));
		if (j == -1)
			return (-1);
		home->f = j;
	}
	else
		return (-1);
	return (0);
}

int	put_textur(char *str, t_text *home, t_cube *cube)
{
	char	*sup;

	sup = ft_strchr(str, '.');
	if (sup)
	{
		if (place_textur(str, sup, home, cube) == 1)
			return (1);
	}
	else
	{
		if (convert_rgb(str, home) == -1)
			return (put_error("color not found: ", str, 1));
	}
	if (!home->door)
		home->door = mlx_xpm_file_to_image(cube->win.mlx_ptr,
				"./textures/door.xpm", &cube->texture.width,
				&cube->texture.height);
	return (0);
}
