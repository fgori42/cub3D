/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:04:07 by fgori             #+#    #+#             */
/*   Updated: 2023/10/13 14:48:19 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	b = 0;
	c = 1;
	while (nptr[a] == ' ' || ((nptr[a] >= 9) && (nptr[a] <= 13)))
		a++;
	if (nptr[a] == '+' || nptr[a] == '-')
	{
		if (nptr[a] == '-')
			c *= -1;
		a++;
	}
	while ((nptr[a] != '\0') && (nptr[a] <= '9') && (nptr[a] >= '0'))
	{
		b = (b * 10) + ((nptr[a] + 2) % 10);
		a++;
	}
	b *= c;
	return (b);
}
/*
#include<stdlib.h>
#include<stdio.h>

int	main(void)
{
	char *f= "   12434567890ad3";
	printf("%i\n | %i ", ft_atoi(f), atoi(f));


}*/
