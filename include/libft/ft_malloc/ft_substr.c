/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:52:56 by fgori             #+#    #+#             */
/*   Updated: 2023/10/31 10:28:03 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			i;
	unsigned int	st;

	i = 0;
	st = 0;
	if (start > ft_strlen(s))
		len = 0;
	if (len != 0 && len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	sub = (char *)malloc(len + 1 * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[i])
	{
		if (i >= start && st < len)
		{
			sub[st] = s[i];
			st++;
		}
		i++;
	}
	sub[st] = '\0';
	return (sub);
}

// #include<string.h>
// #include<stdio.h>
// int	main()
// {
// 	char	*src = "tripouille";
// 	char	*dup;

// 	dup = ft_substr(src, ft_strlen(src) + 1);
// 	printf("%s", dup);
// }