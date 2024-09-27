/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:50:06 by fgori             #+#    #+#             */
/*   Updated: 2023/10/11 11:31:44 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*clone;
	int				i;

	i = 0;
	clone = s;
	n += 1;
	while (n-- > 1)
	{
		clone[i] = c;
		i++;
	}
	return (s);
}
/*
#include<stdio.h>
#include<string.h>
int     main()
{
        char gol[] = "123";
//	ft_memset(gol, '0', sizeof(gol));
	memset(gol, '0', sizeof(gol));
        printf("%s", gol);

}*/
