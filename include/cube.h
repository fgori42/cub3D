/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:06:44 by fgori             #+#    #+#             */
/*   Updated: 2024/09/26 12:48:37 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <pthread.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>
# include <stdbool.h> 

typedef struct s_pos 
{
	float	x;
	float	y;
} t_pos;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_win;

typedef struct s_text
{
	void	*es;
	void	*ov;
	void	*nr;
	void	*sd;
} t_text;

typedef struct s_player
{
	char	type;
	int		angle;
	t_pos	*pos;
	bool	existence;
} t_player;

typedef struct s_map
{
	t_pos	*size;
	char	**map;
	char	**map_check;
} t_map;

typedef struct	s_cube
{
	t_win		win;
	t_map		map;
	t_player	player;
	t_text		texture;
}t_cube;

#endif