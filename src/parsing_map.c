/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:07:52 by fgori             #+#    #+#             */
/*   Updated: 2024/11/07 19:52:05 by aosmenaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	find_max_len(char **mtx)
{
	int	y;
	int	len;
	int	len_max;

	y = 6;
	len_max = -1;
	len = 0;
	while (mtx[y])
	{
		len = ft_strlen(mtx[y]);
		if (len > len_max)
			len_max = len;
		y++;
	}
	return (len_max);
}

static char	*ft_strdup_and_place(char *str, int len)
{
	char	*str2;

	str2 = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(str2, str, ft_strlen(str) + 1);
	return (str2);
}

static void	mtx_clone(t_map *map)
{
	int	i;

	i = 0;
	map->map_check = ft_calloc(size_mtx('y', map->map) + 1, sizeof(char *));
	while (map->map[i])
	{
		map->map_check[i] = ft_strdup(map->map[i]);
		i++;
	}
}

int	mtx_trim(t_map *map, char **mtx, int start)
{
	int		len;
	int		i;
	int		lenstr;
	char	**newmtx;

	i = 0;
	len = size_mtx('y', mtx) - start;
	newmtx = ft_calloc(len + 1, sizeof(char *));
	if (!newmtx)
		return (1);
	lenstr = find_max_len(mtx);
	while (i < len)
	{
		newmtx[i] = ft_strdup_and_place(mtx[start], lenstr);
		start++;
		i++;
	}
	map->map = newmtx;
	mtx_clone(map);
	freeall(mtx);
	return (0);
}

int	find_extra_n(char *str)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	n = 0;
	j = 0;
	while (j < 6)
	{
		while (str[i] && str[i] != '\n')
			i++;
		if (i != n)
		{
			i++;
			n = i;
			j++;
		}
		else if (i == n)
		{
			i++;
			n++;
		}
	}
	return (parse_n(&str[n]));
}
