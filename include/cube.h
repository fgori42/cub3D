/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:06:44 by fgori             #+#    #+#             */
/*   Updated: 2024/11/07 20:00:02 by aosmenaj         ###   ########.fr       */
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

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_input
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	f;
	bool	left;
	bool	right;
	t_pos	dor;
	bool	is_door;
	bool	c;
}	t_input;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_height;
	int		win_width;
}	t_win;

typedef struct s_text
{
	void	*door;
	void	*ea;
	void	*we;
	void	*no;
	void	*so;
	int		f;
	int		c;
}	t_text;

typedef struct s_player
{
	char	type;
	float	angle;
	t_pos	pos;
	bool	existence;
}	t_player;

typedef struct s_map
{
	t_pos	*size;
	char	**map;
	char	**map_check;
	int		level;
}	t_map;

typedef struct s_texture
{
	int	width;
	int	height;
}	t_texture;

typedef struct s_minimap
{
	int	mini_height;
	int	mini_wid;
	int	mini_start_x;
	int	mini_start_y;
}	t_minimap;

typedef struct s_wall
{
	int				idx;
	double			angle;
	double			ray_lenght;
	bool			door;
	t_pos			cor;
	bool			is_door;
	int				wall_top;
	int				wall_bottom;
	int				wall_height;
	double			wall_width;
	int				direction;
	void			*text;
	struct s_wall	*next;
	struct s_wall	*prev;
}	t_wall;

typedef struct s_ray
{
	double	delta_dist_y;
	double	delta_dist_x;
	double	pos_x;
	double	pos_y;
	double	ray_dirx;
	double	ray_diry;
	int		mapx;
	int		mapy;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	hitx;
	double	hity;
	double	ray_length;
	int		id_ray;
	int		num_rays;
	double	fov;
	double	angle_step;
	double	ray_angle;
}	t_ray;

typedef struct s_cube
{
	t_img		*img;
	int			*f;
	int			side;
	int			prev_mouse_x;
	t_win		win;
	t_map		map;
	t_input		input;
	t_player	player;
	t_text		text;
	t_texture	texture;
	t_wall		*inst;
	t_minimap	minimap;
}	t_cube;

int		on_destroy(t_cube *cube);
int		parsing(t_cube *cube, char *str);
int		size_mtx(char size, char **map);
void	img_pixel_put(int color, int x, int y, t_img **img);
void	display_map(t_cube *cube);
int		get_texture_color(void *img, int tex_x, int tex_y);
t_wall	*ft_lstnew_cube(double lenght, t_pos *pos, double angle, t_cube *cube );
t_wall	*ft_lstlast_cube(t_wall *lst);
void	ft_lstadd_back_cube(t_wall **lst, t_wall *new);
void	correct_lst(t_wall *node);
void	draw_animation(t_cube *cube);
void	print_world(t_wall *tmp, t_cube *cube);
bool	hit_vertical(t_wall *node);
void	ft_lstclear_cube(t_wall **lst);
void	calculate_ray(t_cube *cube);
short	wallloak(int x, int y, char **map);
void	ray_init(t_ray *ray, t_cube *cube);
void	ray_calc_init(t_ray *ray, t_cube *cube);
void	ray_calc_step_sidedist(t_ray *ray);
void	determine_hit(t_ray *ray);
int		handle_movement(t_cube *cube);
void	find_wall(t_ray *ray, t_cube *cube);
int		put_textur(char *str, t_text *home, t_cube *cube);
int		put_error(char *str, char *str_two, int i);
bool	map_check(t_cube *cube, char **map);
int		mtx_trim(t_map *map, char **mtx, int start);
int		map_fil(char **map);
bool	is_missing(t_cube *cube);
void	cube_init(t_cube *cube);
int		check_collision(double x, double y, char **map);
int		check_collision(double x, double y, char **map);
int		on_keyrelease(int keysym, t_cube *cube);
int		on_keypress(int keysym, t_cube *cube);
int		get_texture_color(void *img, int tex_x, int tex_y);
int		find_max_len(char **mtx);
int		find_extra_n(char *str);
int		parse_n(char *str);
#endif