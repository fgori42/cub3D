/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:58:26 by fgori             #+#    #+#             */
/*   Updated: 2023/11/08 14:55:12 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printox(void *num)
{
	int	j;

	if (num == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	else
	{
		ft_putstr("0x");
		j = ft_putvod(num);
		j += 2;
	}
	return (j);
}

int	ft_putvod(void *num)
{
	char				*al;
	int					j;
	unsigned long long	prova;

	al = "0123456789abcdef";
	prova = (unsigned long long)num;
	j = 0;
	if (prova > 15)
		j += ft_putvod((void *)(prova / 16));
	j += ft_putchar(al[prova % 16]);
	return (j);
}

int	numlen(unsigned long long ch)
{
	int	len;

	len = 0;
	if (ch == 0)
		return (1);
	while (ch)
	{
		ch /= 10;
		len++;
	}
	return (len);
}
