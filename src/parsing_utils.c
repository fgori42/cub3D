/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:20:34 by fgori             #+#    #+#             */
/*   Updated: 2024/11/10 11:20:37 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	put_error(char *str, char *str_two, int i)
{
	write(2, "ERROR\n", 6);
	write(2, str, ft_strlen(str));
	if (str_two)
		write(2, str_two, ft_strlen(str_two));
	write(2, "\n", 1);
	return (i);
}

char	*skip_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[i] != ' ')
		return (str);
	while (str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}

bool	is_cub(char *str)
{
	char	*tmp;

	tmp = ft_substr(str, ft_strlen(str) - 4, 4);
	if (ft_strncmp(tmp, ".cub", 4) == 0)
	{
		free(tmp);
		return (true);
	}
	else
	{
		free(tmp);
		return (false);
	}
}
