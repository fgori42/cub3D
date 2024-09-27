/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:02:41 by fgori             #+#    #+#             */
/*   Updated: 2023/12/14 14:11:54 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	sortprint(char c, va_list obj)
{
	int	j;

	if (c == 'c')
		j = ft_putchar(va_arg(obj, int));
	if (c == 's')
		j = ft_putstr(va_arg(obj, char *));
	if (c == 'p')
		j = printox(va_arg(obj, void *));
	if (c == 'd')
		j = ft_putnbr(va_arg(obj, int));
	if (c == 'i')
		j = ft_putnbr(va_arg(obj, int));
	if (c == 'u')
		j = ft_putuns(va_arg(obj, int));
	if (c == 'x')
		j = ft_puthex(va_arg(obj, unsigned int), 0, 1);
	if (c == 'X')
		j = ft_puthex(va_arg(obj, unsigned int), 1, 1);
	if (c == '%')
		j = ft_putchar('%');
	return (j);
}

int	ft_printf(const char *str, ...)
{
	va_list	find;
	int		i;
	int		j;
	int		num;

	i = 0;
	num = 0;
	j = 0;
	va_start(find, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			j += sortprint(str[i + 1], find);
			i++;
		}
		else
		{
			ft_putchar(str[i]);
			num++;
		}
		i++;
	}
	va_end(find);
	return (num + j);
}
// #include <stdio.h>
// int main(void)
// {
// 	int	x;
// 	int	a;

// 	x = ft_printf("%u\n", "4294967295");
// 	// a = printf("%ld", -2147483648);
// 	// printf("\nlunghezza ft_printf: %d mentre printf:%d", x, a);
// }
