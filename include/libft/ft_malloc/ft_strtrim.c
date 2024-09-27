/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:03:42 by fgori             #+#    #+#             */
/*   Updated: 2023/10/23 10:38:03 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strchek(char *s, char x)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == x)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		x;
	int		y;
	char	*trim;

	i = 0;
	y = 0;
	x = ft_strlen((char *)s1) - 1;
	while (s1[i] && ft_strchek((char *)set, s1[i]))
		i++;
	while (x > i && ft_strchek((char *)set, s1[x]))
		x--;
	trim = (char *)malloc(((x - i) + 2) * sizeof(char));
	if (!trim)
		return (NULL);
	while (i <= x)
	{
		trim[y] = s1[i];
		y++;
		i++;
	}
	trim[y] = '\0';
	return (trim);
}
/*
#include<stdio.h>
int	main()
{
	char	*str = "sono il mondos";
	char	*set = "ons";
	char	*g = ft_strtrim(str, set);
	printf("%s", g);
}
*/