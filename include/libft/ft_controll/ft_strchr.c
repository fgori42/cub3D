/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:17:01 by fgori             #+#    #+#             */
/*   Updated: 2023/10/25 14:12:38 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;
	int		n;

	i = ft_strlen((char *) s) + 1;
	n = 0;
	str = (char *)s;
	if (c > 127)
		c %= 256;
	while (i > 0)
	{
		if (str[n] == c)
			return (&str[n]);
		n++;
		i--;
	}
	return (NULL);
}
/*
#include<stdio.h>
#include<string.h>
int main(void)
{
    char    str[] = "tripouille";
    char    *g;
	char	*x;

    g = ft_strchr(str, 't' + 256);
	x = strchr(str, 't' + 256);
    printf("%s\n | %s", g, x);
}*/