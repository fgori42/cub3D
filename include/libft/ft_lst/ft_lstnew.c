/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:48:31 by fgori             #+#    #+#             */
/*   Updated: 2023/10/27 11:53:45 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (void *)malloc(sizeof(*new));
	if (!content)
	{
		new->content = NULL;
		new->next = 0;
	}
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
