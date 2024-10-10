/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:06:44 by fgori             #+#    #+#             */
/*   Updated: 2024/10/10 12:24:55 by fgori            ###   ########.fr       */
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

//#ifndef M_PI
//    #define M_PI 3.14159265358979323846
//#endif

typedef struct s_input {
    bool w;
    bool a;
    bool s;
    bool d;
    bool left;
    bool right;
} t_input;

typedef struct s_pos 
{
	float	x;
	float	y;
} t_pos;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_height;
	int		win_width;
} t_win;


typedef struct s_text
{
	void	*EA;
	void	*WE;
	void	*NO;
	void	*SO;
	int		F;
	int		C;
} t_text;

typedef struct s_player
{
	char	type;
	float	angle;
	t_pos	pos;
	bool	existence;
} t_player;

typedef struct s_map
{
	t_pos	*size;
	char	**map;
	char	**map_check;
	int		level;
} t_map;

typedef struct s_texture
{
    char *addr;
    int width;
    int height;
    int bpp; // bits per pixel
    int line_length;
    int endian;
} t_texture;

typedef struct	s_cube
{
	t_win		win;
	t_map		map;
	t_input		input;
	t_player	player;
	t_text		text;
	t_texture	texture;
}t_cube;

int	draw(t_cube *cube);
int	on_destroy(t_win *win);
void draw_square(int x, int y, int color, t_cube *cube);
int	parsing(t_cube *cube, char *str);
int	size_mtx(char size, char **map);
void	display_map(t_cube *cube);

#endif