/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:06:44 by fgori             #+#    #+#             */
/*   Updated: 2024/10/21 12:23:13 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
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
    bool 	w;
    bool 	a;
    bool 	s;
    bool 	d;
    bool 	left;
    bool 	right;
	double	dis;
	bool	c;
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
	void	*door;
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
    int width;
    int height;
} t_texture;

typedef struct s_minimap
{
	int	mini_height;
	int	mini_wid;
	int mini_start_x;
	int	mini_start_y;
}	t_minimap;


typedef struct	s_wall
{
	int				idx;
	double			angle;
	double			ray_lenght;
	double			x;
	double			y;
	int				wall_top;
	int				wall_bottom;
	int 			wall_height;
	double			wall_width;
	int				direction;
	void			*text;
	struct s_wall	*next;
	struct s_wall	*prev;
} t_wall;

typedef struct	s_door
{
	short		is_door;
	t_pos		pos;
}	t_door;

typedef struct	s_cube
{
	t_img		*img;
	int			side;
	int			prev_mouse_x;
	t_win		win;
	t_door		door;
	t_map		map;
	t_input		input;
	t_player	player;
	t_text		text;
	t_texture	texture;
	t_wall		*inst;
	t_minimap	minimap;
}t_cube;

int	draw(t_cube *cube);
int	on_destroy(t_cube *cube);
void draw_square(int x, int y, int color, t_cube *cube);
int	parsing(t_cube *cube, char *str);
int	size_mtx(char size, char **map);
void	img_pixel_put(int color, int x, int y, t_img **img);
void	display_map(t_cube *cube);
int get_texture_color(void *img, int tex_width, int tex_height, int tex_x, int tex_y);

t_wall	*ft_lstnew_cube(double lenght, t_pos *pos, double angle, t_cube *cube );
t_wall	*ft_lstlast_cube(t_wall *lst);
void	ft_lstadd_back_cube(t_wall **lst, t_wall *new);
void	correct_lst(t_wall *node);


#endif