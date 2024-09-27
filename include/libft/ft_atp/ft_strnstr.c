/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:06:28 by fgori             #+#    #+#             */
/*   Updated: 2023/10/25 15:54:17 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*str;
	char	*to_find;
	size_t	i;
	size_t	j;

	str = (char *)big;
	to_find = (char *)little;
	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (str);
	while (str[i] != '\0' && i < len)
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0' && i + j < len)
		{
			j++;
		}
		if (to_find[j] == '\0')
			return (&str[i]);
		i++;
		j = 0;
	}
	return (NULL);
}

// #include<stdio.h>

// int	main()
// {
// 	char	str[] = "aaabcabcd";
// 	//char	to_find[] = "aabc";

// 	printf("%s", ft_strnstr(str, "cd", 8));
// }