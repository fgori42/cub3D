/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:28:08 by fgori             #+#    #+#             */
/*   Updated: 2023/10/21 12:11:33 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	long int		len;
	char			*new;

	i = 0;
	len = ft_strlen((char *)s);
	new = (char *)malloc(len + 1 * sizeof(char));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
/*
char	toato(unsigned int i, char n)
{
	n += i;
	return (n);
}

#include<stdio.h>
int	main ()
{
	char	*arr = "CIAO SONO UN GATTO";
	char	*fin;

	fin = ft_strmapi(arr, toato);
	printf("%s", fin);
}*/