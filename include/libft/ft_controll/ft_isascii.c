/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:52:11 by fgori             #+#    #+#             */
/*   Updated: 2023/10/10 18:32:09 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include<ctype.h>
#include<unistd.h>

int	main(void)
{
	int	c;

	c = 'a';
	if ((isascii(c)) ? 1 : 0 )
		write(1, "R", 1);
	else
		write(1, "f", 1);
}*/
