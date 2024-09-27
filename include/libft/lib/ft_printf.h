/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:03:31 by fgori             #+#    #+#             */
/*   Updated: 2023/11/07 12:06:49 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int nb);
int	ft_puthex(unsigned int i, int x, int cont);
int	ft_putuns(unsigned int nb);
int	ft_putvod(void *num);
int	numlen(unsigned long long ch);
int	ft_printf(const char *str, ...);
int	printox(void *num);

#endif
