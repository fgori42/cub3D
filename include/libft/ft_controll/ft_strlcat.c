/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:25:05 by fgori             #+#    #+#             */
/*   Updated: 2023/10/24 11:42:00 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	a;
	size_t	c;
	size_t	i;

	a = 0;
	i = 0;
	c = 0;
	while (dest[i])
		i++;
	while (src[a])
		a++;
	if (size <= i)
		a += size;
	else
		a += i;
	while (src[c] && i + 1 < size)
	{
		dest[i] = src[c];
		i++;
		c++;
	}
	dest[i] = '\0';
	return (a);
}
/*
#include<stdio.h>
	int    main(void)
	{
	    char    src[] = "12345";
	    char    dest[] = "ciao";
	    int	c;

	    c =  ft_strlcat(dest, src, 7);
	    printf("%s | %d", dest, c);
	}*/
