/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:42:06 by fgori             #+#    #+#             */
/*   Updated: 2023/11/20 18:03:49 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

char	*get_next_line(int fd)
{
	static char	*mat[4096];
	char		*sup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	mat[fd] = make_line(mat[fd], fd);
	if (!mat[fd])
		return (NULL);
	if (!mat[fd][0])
		return (NULL);
	sup = only_new(mat[fd]);
	mat[fd] = control(mat[fd], ft_strlen(sup));
	if (!sup[0] && !mat[fd][0])
	{
		free(sup);
		sup = 0;
		free(mat[fd]);
		mat[fd] = 0;
	}
	return (sup);
}

char	*make_line(char *dest, int fd)
{
	ssize_t		cont;
	char		*file;

	file = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!file)
		return (NULL);
	cont = 1;
	while (cont != 0 && !ft_strchr(dest, '\n'))
	{
		cont = read(fd, file, BUFFER_SIZE);
		if (cont == -1)
		{
			free(file);
			return (NULL);
		}
		if (cont != 0)
		{
			file[cont] = '\0';
			dest = concat(dest, file, cont);
		}
	}
	free(file);
	return (dest);
}

char	*only_new(char *dest)
{
	size_t		i;
	char		*new;
	size_t		j;

	j = 0;
	while (dest[j] && dest[j] != '\n')
		j++;
	if (dest[j] == '\n')
		j++;
	new = (char *)malloc(j + 1 * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < j)
	{
		new[i] = dest[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*control(char *dest, int i)
{
	int		z;
	int		n;
	char	*clean;

	n = 0;
	z = ft_strlen(dest) - i;
	if (!dest[n] || z == 0)
	{
		free(dest);
		return (NULL);
	}
	clean = (char *)malloc(z + 1 * sizeof(char));
	if (!clean)
		return (NULL);
	while (n < z)
	{
		clean[n] = dest[i];
		i++;
		n++;
	}
	clean[n] = '\0';
	free(dest);
	return (clean);
}

// int	main(void)
// {
// 	//char	str[] = "sono la stella del telefonino";
// 	int		i = 0;
// 	int	fd = open("prova.txt", O_RDONLY);
// 	// int		fd = fileno(file);
// 	char *st;
// 	while (i < 6)
// 	{
// 		st = get_next_line(fd);
// 		printf("%s", st);
// 		free(st);
// 		i++;
// 	}
// 	close(fd);
// }