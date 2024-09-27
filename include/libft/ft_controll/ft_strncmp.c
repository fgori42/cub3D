/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:42:06 by fgori             #+#    #+#             */
/*   Updated: 2023/10/21 13:51:26 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (((i < n) && (s1[i] == s2[i]))
		&& s2[i])
	{
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}
/*#include <stdio.h>
int	main()
{
	char	*s1;
	   s1	= "\200";
	char	*s2;
	   s2	= "\0";

	printf("%i", ft_strncmp(s1, s2, 2));
	return (0);
}*/