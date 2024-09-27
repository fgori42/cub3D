/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:53:41 by fgori             #+#    #+#             */
/*   Updated: 2024/01/09 13:43:16 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	freeall(char **mat, int h)
{
	int	n;

	n = 0;
	while (n < h)
	{
		if (mat[n] != NULL)
		{
			free(mat[n]);
			mat[n] = NULL;
		}
		n++;
	}
	free(mat);
}

static void	fillstr(char **mat, char *fil, char c, int find)
{
	int		i;
	int		x;
	int		j;

	i = 0;
	x = 0;
	j = 0;
	while (fil[j] == c)
		j++;
	if (j > 0)
		x = j;
	while (i < find)
	{
		while (fil[j] != c && fil[j] != '\0')
			j++;
		mat[i] = ft_substr(fil, x, (j - x));
		if (!mat[i])
			return (freeall(mat, i));
		while (fil[j] == c)
			j++;
		x = j;
		i++;
	}
	mat[i] = NULL;
}

static int	framcont(char *s, char c)
{
	int	i;
	int	x;
	int	g;

	i = 0;
	x = 0;
	g = 0;
	while (s[g])
	{
		if (s[g] != c && x == 0)
		{
			x = 1;
			i++;
		}
		else if (s[g] == c)
			x = 0;
		g++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		num;
	char	**mat;

	num = framcont((char *) s, c);
	mat = (char **)ft_calloc(num + 1, sizeof(char *));
	if (!mat)
		return (NULL);
	fillstr(mat, (char *)s, c, num);
	return (mat);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	**arr;
// 	int	i;

// 	arr = ft_split("tripouille\0", ' ');
// 	i = 0;
// 	while (arr[i] != NULL)
// 	{
// 		printf("%s\n", arr[i]);
// 		i++;
// 	}
// 	if (arr[i] == NULL)
// 		printf("NULL");
// 	return (0);
// }