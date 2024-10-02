/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:47:00 by fgori             #+#    #+#             */
/*   Updated: 2024/10/01 18:45:26 by fgori            ###   ########.fr       */
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

int	crToInt(char *str)
{
	int	i;
	int	val;

	val = 0;
	i = 0;
	while(str[i])
	{
		val +=str[i];
		i++;
	}
	return (val);
}

void	take_textur(t_cube *cube, char **text)
{
	int 	i;
	//char	*sup;

	i = 0;
	(void)cube;
	(void)text;
	printf("valore NO = %d\nvalore SO = %d\nvalore EA = %d\nvalore WE = %d\n", crToInt("NO"), crToInt("SO"), crToInt("EA"), crToInt("WE"));
	while (i < 6)
	{
		if 
			
	}
}

int parsing(t_cube *cube, char *str)
{
	char	*mapFile;
	char	**openMap;
	(void)cube;

	if (!is_cub(str))
		return (1);
	write(2, "qui\n", 4);
	mapFile = gnl(str);
	if (!mapFile)
		return (1);
	openMap = ft_split(mapFile, '\n');	
	free(mapFile);
	take_textur(cube, openMap);
	return (0);
}
