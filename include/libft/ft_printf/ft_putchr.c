/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:53:45 by fgori             #+#    #+#             */
/*   Updated: 2023/11/08 15:12:21 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nb)
{
	int	s;

	s = 0;
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		ft_putnbr(147483648);
		return (11);
	}
	if (nb < 0)
	{
		s += ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
	}
	return (numlen(nb) + s);
}

int	ft_puthex(unsigned int i, int x, int cont)
{
	char	*al;
	int		j;

	if (x == 0)
		al = "0123456789abcdef";
	else
		al = "0123456789ABCDEF";
	if (i <= 15)
	{
		j = i % 16;
		ft_putchar(al[j]);
	}
	else
	{
		cont = ft_puthex(i / 16, x, cont + 1);
		cont = ft_puthex(i % 16, x, cont);
	}
	return (cont);
}

int	ft_putuns(unsigned int nb)
{
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
	}
	return (numlen(nb));
}
