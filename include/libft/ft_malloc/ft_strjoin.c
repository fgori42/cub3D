/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:29:19 by fgori             #+#    #+#             */
/*   Updated: 2024/09/24 14:56:12 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	strwrite(char *s, const char *s2, int n, int i)
{
	while (s2[i] != '\0')
	{
		s[n] = s2[i];
		n++;
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		step;
	int		i;

	step = ft_strlen((char *)s1);
	join = (char *)malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	strwrite(join, s1, 0, 0);
	strwrite(join, s2, step, 0);
	i = (ft_strlen((char *)s2) + step);
	join[i] = '\0';
	return (join);
}
/*
#include<stdio.h>
int	main()
{
	char	*s = "1234";
	char	*g = "56789";
	char	*x;
	x = ft_strjoin(s, g);
	printf("%s", x);
}*/
