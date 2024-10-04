/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:47:00 by fgori             #+#    #+#             */
/*   Updated: 2024/10/04 17:25:46 by fgori            ###   ########.fr       */
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


char *gnl(char *str)
{
	int 	fd;
	int		control;
	char	*buff;
	char 	*txt;
	char	*sup;
	
	control = 1;
	buff = ft_calloc(2,1);
	txt = ft_calloc(1,1);
	fd = open(str,  O_RDWR );
	if (fd < 0)
		return (NULL);
	while (control > 0)
	{
		control = read(fd, buff, 1);
		sup = txt;
		txt = ft_strjoin(txt, buff);
		free(sup);
	}
	free(buff);
	return(txt);
}

int create_rgb(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**sup;

	sup = ft_split(str, ',');
	r = ft_atoi(sup[0]);
	g = ft_atoi(sup[1]);
	b = ft_atoi(sup[2]);
	free(str);
	free(sup);
    return (r << 16 | g << 8 | b);
}

int	put_textur(char *str, t_text *home)
{
	char *sup;

	sup = ft_strchr(str, '.');
	if (sup)
	{
		if (!home->NO && ft_strncmp(str, "NO", 2) == 0 )
			home->NO = ft_strdup(sup);
		else if (!home->SO && ft_strncmp(str, "SO", 2) == 0 )
			home->SO = ft_strdup(sup);
		else if (!home->EA && ft_strncmp(str, "EA", 2) == 0 )
			home->EA = ft_strdup(sup);
		else if (!home->WE && ft_strncmp(str, "WE", 2) == 0 )
			home->WE = ft_strdup(sup);
	}
	else
	{
		if (!home->C && ft_strncmp(str, "C", 1))
			home->C = create_rgb(ft_strtrim(str, "C "));
		else if (!home->F && ft_strncmp(str, "F", 1))
			home->F = create_rgb(ft_strtrim(str, "F "));
	}
	return (1);
}

int	mtx_trim(t_map	*map, char **mtx, int start)
{
	int		len;
	int		i;
	char	**newMtx;

	i = 0;
	len = size_mtx('y', mtx);
	newMtx = ft_calloc(len - start, sizeof(char *));
	if (!newMtx)
		return (1);
	while (newMtx[i] && i < start)
	{
		newMtx[i] = ft_strdup(mtx[start]);
		start++;
		i++;
	}
	map->map = newMtx;
	i = 0;
	map->map_check = ft_calloc(size_mtx('y', newMtx), sizeof(char *));
	while(map->map[i])
	{
		map->map_check[i] = ft_strdup(map->map[i]);
		i++;
	}
	free(mtx);
	return (0);
}

bool	take_textur(t_cube *cube, char **text)
{
	int 	i;
	char	*jj;

	i = 0;
	while (i < 6)
	{
		jj = text[i];
		if (ft_strncmp(text[i], "NO", 2) == 0 || ft_strncmp(text[i], "SO", 2) == 0
			|| ft_strncmp(text[i], "WE", 2) == 0 || ft_strncmp(text[i], "EA", 2) == 0
			|| ft_strncmp(text[i], "C", 1) == 0 || ft_strncmp(text[i], "F", 1) == 0) 
			{
			if (put_textur(text[i], &cube->text) == 1)
				return (false);
			}
		else
			return (false);
		i++;
	}
	if (mtx_trim(&cube->map, text,i) == 1)
		return (false);
	return (true);
}

int parsing(t_cube *cube, char *str)
{
	char	*mapFile;
	char	**openMap;

	if (!is_cub(str))
		return (1);

	mapFile = gnl(str);
	if (!mapFile)
		return (1);
	openMap = ft_split(mapFile, '\n');	
	free(mapFile);
	if (take_textur(cube, openMap) == false)
		return (1);
	return (0);
}
