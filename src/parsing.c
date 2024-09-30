/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:47:00 by fgori             #+#    #+#             */
/*   Updated: 2024/09/30 15:12:22 by fgori            ###   ########.fr       */
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
	
	control = 1;
	txt = ft_calloc(1,1);
	fd = open(str,  O_RDWR );
	if (fd < 0)
		return (NULL);
	while (control > 0)
	{
		control = read(fd, buff, 1);
		txt = ft_strjoin(txt, buff);
		free(buff);
	}
	return(txt);
}

int parsing(t_cube *cube, char *str)
{
	int		fd;
	char	*mapFile;
	char	**openMap;
	(void)cube;

	if (!is_cub(str))
		return (1);
	mapFile = gnl(str);	
	openMap = ft_split(mapFile, '\n');		
	
}
