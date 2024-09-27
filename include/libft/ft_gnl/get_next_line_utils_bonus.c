/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:51:13 by fgori             #+#    #+#             */
/*   Updated: 2023/12/14 14:10:41 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*concat(char *dest, char *src, ssize_t size)
{
	int		i;
	int		j;
	char	*con;

	if (!dest)
	{
		dest = (char *)malloc(1);
		dest[0] = '\0';
	}
	con = (char *)malloc((ft_strlen(dest) + size) + 1 * sizeof(char));
	if (!con)
		return (NULL);
	i = -1;
	j = 0;
	while (dest[++i])
		con[i] = dest[i];
	while (src[j])
	{
		con[i] = src[j];
		i++;
		j++;
	}
	con[i] = '\0';
	free(dest);
	return (con);
}
