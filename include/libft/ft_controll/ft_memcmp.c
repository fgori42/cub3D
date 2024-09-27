/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:12:28 by fgori             #+#    #+#             */
/*   Updated: 2023/10/21 14:05:52 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*str2;
	size_t			i;

	str = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (i < n && str[i] == str2[i])
	{
		i++;
	}
	if (i < n)
		return ((unsigned char)str[i] - (unsigned char)str2[i]);
	else
		return (0);
}
/*#include <stdio.h>

int	main()
{
	char	*s1;
	   s1	= "ciao sono io";
	char	*s2;
	   s2	= "Ciao sono io";

	printf("%i", ft_memcmp(s1, s2, 2));
	return (0);
}*/
