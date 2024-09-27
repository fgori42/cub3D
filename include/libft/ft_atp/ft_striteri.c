/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:36:17 by fgori             #+#    #+#             */
/*   Updated: 2023/10/24 11:54:13 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}
/*
void	toato(unsigned int i, char *n)
{
	n[i] +32;
	return (n);
}

#include<stdio.h>
int	main ()
{
	char	*arr = "CIAO SONO UN GATTO";
	char	*fin;

	ft_striteri(arr, toato);
	printf("%s", arr);
}*/