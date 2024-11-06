/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:47:00 by fgori             #+#    #+#             */
/*   Updated: 2024/11/06 11:35:19 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	is_cub(char *str)
{
	char	*tmp;

	tmp = ft_substr(str, ft_strlen(str) - 4, 4);
	if (ft_strncmp(tmp, ".cub", 4) == 0)
	{
		free(tmp);
		return (true);
	}
	else
	{
		free(tmp);
		return (false);
	}
}

char	*gnl(char *str)
{
	int		fd;
	int		control;
	char	*buff;
	char	*txt;
	char	*sup;

	control = 1;
	buff = ft_calloc(2, 1);
	txt = ft_calloc(1, 1);
	if (!txt || !buff)
		return (NULL);
	fd = open(str, O_RDWR);
	if (fd < 0)
		return (NULL);
	while (control > 0)
	{
		control = read(fd, buff, 1);
		if (control < 1)
			break ;
		sup = txt;
		txt = ft_strjoin(txt, buff);
		free(sup);
	}
	free(buff);
	return (txt);
}

bool	take_textur(t_cube *cube, char **text)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(text[i], "NO", 2) == 0 || ft_strncmp(text[i], "SO",
				2) == 0 || ft_strncmp(text[i], "WE", 2) == 0
			|| ft_strncmp(text[i], "EA", 2) == 0 || ft_strncmp(text[i], "C",
				1) == 0 || ft_strncmp(text[i], "F", 1) == 0)
		{
			if (put_textur(text[i], &cube->text, cube) == 1)
				return (false);
		}
		else
			return (false);
		i++;
	}
	if (mtx_trim(&cube->map, text, i) == 1)
		return (perror("Error\nimpossible to trim mtx"), false);
	return (true);
}

int	put_error(char *str, char *str_two, int i)
{
	write(2, "ERROR\n", 6);
	write(2, str, ft_strlen(str));
	if (str_two)
		write(2, str_two, ft_strlen(str_two));
	write(2, "\n", 1);
	return (i);
}

int	parsing(t_cube *cube, char *str)
{
	char	*mapfile;
	char	**openmap;

	if (!is_cub(str))
		return (1);
	mapfile = gnl(str);
	if (!*(mapfile))
		return (1);
	openmap = ft_split(mapfile, '\n');
	free(mapfile);
	if (!take_textur(cube, openmap))
	{
		freeall(openmap);
		return (1);
	}
	if (!map_check(cube, cube->map.map_check))
		return (1);
	if (!is_missing(cube))
		return (perror("ERROR\nmissing textur\n"), 1);
	return (map_fil(cube->map.map_check));
}
