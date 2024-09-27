/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:21:04 by fgori             #+#    #+#             */
/*   Updated: 2023/10/21 11:08:33 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				g;
	unsigned char		*destc;
	unsigned char		*srcc;

	g = 0;
	if (!dest && !src)
		return (dest);
	destc = ((unsigned char *)dest);
	srcc = ((unsigned char *)src);
	if (srcc < destc)
	{
		while (n-- > 0)
			destc[n] = srcc[n];
	}
	else
	{
		while (g < n)
		{
			destc[g] = srcc[g];
			g++;
		}
	}
	return (dest);
}
/*
#include <string.h>
#include<stdio.h>
int	main()
{
	char *src= "ciao";
	//char dest[0];
	//char aaa[0];
	size_t	i;

	i = 20;
	//ft_memmove(NULL, src, i);
	//memmove(NULL, src, i);
	printf("%s\n",(char *)ft_memmove(NULL, src, i)(char *)memmove(NULL, src, i));
}*/