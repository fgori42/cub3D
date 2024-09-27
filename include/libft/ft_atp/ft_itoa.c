/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:25:46 by fgori             #+#    #+#             */
/*   Updated: 2023/10/24 11:33:10 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnb(char *s, int n, int len)
{
	if (n == 0)
		s[0] = '0';
	if (n == -2147483648)
	{
		s[0] = '-';
		s[1] = '2';
		n = 147483648;
	}
	if (n >= 0)
	{
		while (len >= 0 && n)
		{
			s[len] = n % 10 + '0';
			n /= 10;
			len--;
		}
	}
	else
	{
		s[0] = '-';
		n *= -1;
		putnb(s, n, len);
	}
}

static int	cont(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		x;

	x = cont(n);
	if (n < 0)
	{
		x += 2;
		num = (char *)malloc(x * sizeof(char));
	}
	else
	{
		x++;
		num = (char *)malloc(x * sizeof(char));
	}
	if (!num)
		return (NULL);
	x -= 1;
	num[x] = '\0';
	putnb(num, n, x - 1);
	return (num);
}
/*
#include<stdio.h>
int main(void)
{
	int	i = 1442;
	char *s;
	s = ft_itoa(i);
	printf("%s", s);
}*/