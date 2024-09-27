/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:50:33 by fgori             #+#    #+#             */
/*   Updated: 2023/10/30 21:31:37 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	char	con;
	size_t	i;
	size_t	cont;

	i = 0;
	cont = ft_strlen(s);
	if (n == 0)
		return (NULL);
	if ((n < cont) && (c == 0))
	{
		return (NULL);
	}
	str = (char *)s;
	if (!c)
		return (&str[ft_strlen((char *)s)]);
	con = (char)c;
	while (i < n)
	{
		if (str[i] == con)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

// #include<stdio.h>
// #include<string.h>
// int main(void)
// {
//     char    str[] = {0, 1, 2, 3, 4, 5};
//     char    *g;
//     char	*x;

//     g = ft_memchr(str, 1, 3);
//     //g[0] = 'c';
//     x = memchr(str, 1, 2);
//     printf("%s\n | %s", g, x);
// }