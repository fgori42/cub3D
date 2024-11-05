/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:09 by fgori             #+#    #+#             */
/*   Updated: 2024/11/05 12:50:36 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int side1;

#include "cube.h"
#include "libft.h"

#define MAX_DISTANCE sqrt((1600 * 900) + (1600* 900))

short	wallLoak(int x, int y, char **map)
{
	x /= 64;
	y /= 64;
	if (map[y][x] == 'D')
		return (2);
    if (map[y][x] == '1')
		return (1);
    return (0);
}

int	size_mtx(char size, char **map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (size == 'x')
	{
		while(map[y][x])
			x++;
		return(x);
	}
	if (size == 'y')
	{
		while(map[y])
			y++;
		return (y);
	}
	return (0);
}

float CentInSis(const float bn)
{
	int ful;
	int six;
	int cent;
	float newNb;

	ful = (int)bn;
	cent = (int)((bn - ful) * 100);
	six = (cent *64) / 100;
	newNb = (ful + ((float)six / 100));
	return (newNb);
}

int get_texture_color(void *img, int tex_width, int tex_height, int tex_x, int tex_y)
{
    char    *pixel_data;
    int     color;
    int     bpp;
    int     size_line;
    int     endian;

    // Get the address of the image data (pixel array)
    pixel_data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    // Ensure tex_x and tex_y are within the bounds of the texture dimensions
    if (tex_x >= tex_width) tex_x = tex_width - 1;
	if (tex_x < 0) tex_x = 0;
    if (tex_y >= tex_height) tex_y = tex_height - 1;
	if (tex_y < 0) tex_y = 0;
    // Calculate the pixel's offset in the image's data array
    int pixel_offset = tex_y * size_line + tex_x * (bpp / 8);
	if (endian == 0) 
	{
        // Little-endian: the color is stored as BGR(A)
        color = *(int *)(pixel_data + pixel_offset);
    } 
	else 
	{
        // Big-endian: the color is stored as RGB(A)
        unsigned char r = pixel_data[pixel_offset];
        unsigned char g = pixel_data[pixel_offset + 1];
        unsigned char b = pixel_data[pixel_offset + 2];
        color = (r << 16) | (g << 8) | b; // Assemble RGB into an int
    }
    // Get the color of the pixel (dereference the pointer at the offset)
    color = *(int *)(pixel_data + pixel_offset);
    return color;
}

bool	hit_vertical(t_wall *node)
{	
	if (node->direction == 1 || node->direction == 3)
		return true; // Raggio ha colpito una parete verticale
	else
		return false; // Raggio ha colpito una parete orizzontale
}

void	img_pixel_put(int color, int x, int y, t_img **img)
{
	char *pixel;

	if (y < 0 || y > 900)
		return ;
	if (x < 0 || x > 1600)
		return ;
	pixel = (*img)->data + ((y * (*img)->size_line) + (x * (*img)->bpp / 8));
	*(int *)pixel = color; 
}

void ray_init(t_ray *ray, t_cube *cube)
{
	ray->id_ray = 0;
	ray->num_rays =  cube->win.win_width;
    ray->FOV = 60 * (M_PI / 180); // 60-degree FOV
    ray->angle_step = ray->FOV / ray->num_rays; // Angle step for each ray
    ray->ray_angle = cube->player.angle - (ray->FOV / 2); // Start at the left edge of the FOV
	if (ray->ray_angle < 0)
    	ray->ray_angle += 2 * M_PI;
    if (ray->ray_angle > 2 * M_PI)
    	ray->ray_angle -= 2 * M_PI;
}

void ray_calc_init(t_ray *ray, t_cube *cube)
{
	ray->hit = 0;
	// Player's position
	ray->posX = cube->player.pos.x;
	ray->posY = cube->player.pos.y;

	// Ray direction based on current ray angle
	ray->rayDirx = cos(ray->ray_angle);
	ray->rayDiry = sin(ray->ray_angle);

	// Which box of the map we're in
	ray->mapx = (int)(ray->posX);
	ray->mapy = (int)(ray->posY);

	// Length of the ray from one x or y-side to the next x or y-side
	ray->delta_dist_x = fabs(1 / ray->rayDirx);
	ray->delta_dist_y = fabs(1 / ray->rayDiry);
}

void ray_calc_step_sidedist(t_ray *ray)
{
	if (ray->rayDirx < 0)
	{
		ray->stepX = -1;
		ray->side_dist_x = (ray->posX - ray->mapx) * ray->delta_dist_x;
	}
	else
	{
		ray->stepX = 1;
		ray->side_dist_x = ((ray->mapx + 1.0) - ray->posX) * ray->delta_dist_x;
	}
	if (ray->rayDiry < 0)
	{
		ray->stepY = -1;
		ray->side_dist_y = (ray->posY - ray->mapy) * ray->delta_dist_y;
	}
	else
	{
		ray->stepY = 1;
		ray->side_dist_y = ((ray->mapy + 1.0) - ray->posY) * ray->delta_dist_y;
	}
}

void find_wall(t_ray *ray, t_cube *cube)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->mapx += ray->stepX;
			ray->side = 0;
			cube->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->mapy += ray->stepY;
			ray->side = 1;
			cube->side = 1;
		}
		// Check if the ray has hit a wall
		if (wallLoak(ray->mapx, ray->mapy, cube->map.map))
			ray->hit = 1;
	}
}

void determine_hit(t_ray *ray)
{
	if (ray->side == 0)
	{
		// Vertical wall hit
		ray->hitx = ray->posX + ray->side_dist_x * ray->rayDirx;
		ray->hity = ray->posY + ray->side_dist_x * ray->rayDiry;
	}
	else
	{
		// Horizontal wall hit
		ray->hitx = ray->posX + ray->side_dist_y * ray->rayDirx;
		ray->hity = ray->posY + ray->side_dist_y * ray->rayDiry;
	}
	if (ray->side == 0)
		ray->ray_length = (ray->mapx - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirx;
	else
		ray->ray_length = (ray->mapy - ray->posY + (1 - ray->stepY) / 2) / ray->rayDiry;
}

void calculate_ray(t_cube *cube)
{
    t_ray ray;
    t_wall	*tmp;
	t_pos	pos;
	ray_init(&ray, cube);
    while (ray.id_ray < ray.num_rays)
    {
		ray_calc_init(&ray, cube);
		ray_calc_step_sidedist(&ray);
		find_wall(&ray, cube);
		determine_hit(&ray);
		pos.x = ray.hitx;
		pos.y = ray.hity;
		tmp = ft_lstnew_cube(ray.ray_length, &pos, ray.ray_angle, cube);
		ft_lstadd_back_cube(&cube->inst, tmp);
        ray.ray_angle += ray.angle_step;
        if (ray.ray_angle < 0)
    		ray.ray_angle += 2 * M_PI;
    	if (ray.ray_angle > 2 * M_PI)
    		ray.ray_angle -= 2 * M_PI;
        ray.id_ray++;
    }
	correct_lst(cube->inst);
	print_world(cube->inst, cube);
}

void draw_direction(t_img *img, t_cube *cube)
{
	int tmpx; 
	int tmpy;
	double ray_x;
	double ray_y;
	double ray_length;

	ray_length = 0;
	tmpx = (int)((cube->player.pos.x / 2) / 64) + 4.5 * 32;
	tmpy = (int)((cube->player.pos.y / 2) / 64) + 2.5 * 32;
	while (ray_length < 32)
	{
		ray_x = (tmpx + cos(cube->player.angle) * ray_length);
    	ray_y = (tmpy + sin(cube->player.angle) * ray_length);
		img_pixel_put(0x00FF00, (int)ray_x, (int)ray_y, &img);
		ray_length++;
	}
}

void	free_textur(t_cube *cube)
{
	if (cube->text.NO)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.NO);
	if (cube->text.EA != NULL)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.EA);
	if (cube->text.SO)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.SO);
	if (cube->text.WE)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.WE);
	if (cube->text.door)
		mlx_destroy_image(cube->win.mlx_ptr, cube->text.door);	
}

int     on_destroy(t_cube *cube)
{
	if (cube->map.map)
		freeall(cube->map.map);
	if (cube->map.map_check)
		freeall(cube->map.map_check);
	free_textur(cube);
	if (cube->inst)
		ft_lstclear_cube(&cube->inst);
	if (cube->win.win_ptr)
			mlx_destroy_window(cube->win. mlx_ptr, cube->win.win_ptr);
	if (cube->win.mlx_ptr)
	{
		mlx_destroy_display(cube->win.mlx_ptr);
		free(cube->win.mlx_ptr);
	}
	exit(0);
	return (0);
}

static void	strwrite(char *s, const char *s2, int n, int i)
{
	while (s2[i] != '\0')
	{
		s[n] = s2[i];
		n++;
		i++;
	}
}
char	*ft_strjoins(char *s1, char const *s2)
{
	char	*join;
	int		step;
	int		i;

	if (!s1)
		s1 = ft_calloc(1,1);
	step = ft_strlen((char *)s1);
	join = (char *)malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	strwrite(join, s1, 0, 0);
	strwrite(join, s2, step, 0);
	i = (ft_strlen((char *)s2) + step);
	join[i] = '\0';
	return (join);
}

void	door_open(t_cube *cube)
{
	float angle;
	
	angle = cube->player.angle;
	double ray_x = cube->player.pos.x + cos(angle) * 60;
	double ray_y = cube->player.pos.y + sin(angle) * 60;
	int x = (int)ray_x / 64;
	int y = (int)ray_y / 64;
	if (cube->map.map[y][x] == 'd')
		cube->map.map[y][x] = 'D';
	else if (cube->map.map[y][x] == 'D')
		cube->map.map[y][x] = 'd';	
}

int	on_keypress(int keysym, t_cube *cube)
{
	if (keysym == XK_W || keysym == XK_w)
		cube->input.w = true;
	else if (keysym == XK_A || keysym == XK_a)
		cube->input.a = true;
	else if (keysym == XK_S || keysym == XK_s)
		cube->input.s = true;
	else if (keysym == XK_D || keysym == XK_d)
		cube->input.d = true;
	if (keysym == XK_F || keysym == XK_f)
		cube->input.f = true;
	if (keysym == XK_c)
		cube->input.c = true;
	if (keysym == XK_e)
		door_open(cube);
	if (keysym == XK_m)
	{
		cube->map.level++;
		if (cube->map.level > 2)
			cube->map.level = 0;
	}
	if (keysym == XK_Left)
		cube->input.left = true;
	if (keysym == XK_Right)
		cube->input.right = true;
	if (keysym == XK_Escape)
		on_destroy(cube);
	return (0);
}

int on_keyrelease(int keysym, t_cube *cube)
{
	if (keysym == XK_W || keysym == XK_w)
		cube->input.w = false;
	if (keysym == XK_A || keysym == XK_a)
		cube->input.a = false;
	if (keysym == XK_S || keysym == XK_s)
		cube->input.s = false;
	if (keysym == XK_D || keysym == XK_d)
		cube->input.d = false;
	if (keysym == XK_c)
		cube->input.c = false;
	if (keysym == XK_Left)
		cube->input.left = false;
	if (keysym == XK_Right)
		cube->input.right = false;
	return (0);
}


int check_collision(double x, double y, char **map)
{
	double player_size;
	
	player_size = 5;
	if (wallLoak(x - player_size, y - player_size, map) ||
		wallLoak(x + player_size, y - player_size, map) ||
		wallLoak(x - player_size, y + player_size, map) ||
		wallLoak(x + player_size, y + player_size, map))
	{
		return 0;
	}
	return 1;
}

int	check_mov(double angle, t_cube cube)
{
	double	ray_y;
	double	ray_x;

	ray_x = cube.player.pos.x + cos(angle) * 20;
	ray_y = cube.player.pos.y + sin(angle) * 20;
    if (!check_collision(ray_x, ray_y, cube.map.map))
    	return (1);
	else
		return (0);
}


int check_distance(t_cube cube, char direction)
{
	float	angle;
	
	if (direction == 'a')
		angle = cube.player.angle - (90 * M_PI / 180);
	else if (direction == 'd')
		angle = cube.player.angle + (90 * M_PI / 180);
	else if (direction == 's')
		angle = cube.player.angle + (180 * M_PI / 180);
	else
		angle = cube.player.angle;
	if (angle < 0)
    	angle += 2 * M_PI;
    if (angle > 2 * M_PI)
	{
    	angle -= 2 * M_PI;
	}
	return(check_mov(angle, cube));
}

int handle_movement(t_cube *cube)
{
    double move_step = 10; // Movement speed
    double rot_step = 0.08; // Rotation speed (radians)

    // Handle forward movement
    if (cube->input.w && !check_distance(*cube, 'w'))
	{
        double new_x = cube->player.pos.x + cos(cube->player.angle) * move_step;
        double new_y = cube->player.pos.y + sin(cube->player.angle) * move_step;
        if (check_collision(new_x, new_y, cube->map.map))
        {
            cube->player.pos.x = new_x;
            cube->player.pos.y = new_y;
        }
    }
    // Handle backward movement
    if (cube->input.s && !check_distance(*cube, 's')) {
        double new_x = cube->player.pos.x - cos(cube->player.angle) * move_step;
        double new_y = cube->player.pos.y - sin(cube->player.angle) * move_step;
        if (check_collision(new_x, new_y, cube->map.map))
        {
            cube->player.pos.x = new_x;
            cube->player.pos.y = new_y;
        }
    }
   	// Handle left/right movement (strafing)
    if (cube->input.a && !check_distance(*cube, 'a'))
	{
		double new_x = cube->player.pos.x - cos(cube->player.angle + (90 * M_PI / 180)) * move_step;
        double new_y = cube->player.pos.y - sin(cube->player.angle + (90 * M_PI / 180)) * move_step;
        if (check_collision(new_x, new_y, cube->map.map))
        {
            cube->player.pos.x = new_x;
            cube->player.pos.y = new_y;
        }
	}
    if (cube->input.d && !check_distance(*cube, 'd'))
    {
		double new_x = cube->player.pos.x - cos(cube->player.angle - (90 * M_PI / 180)) * move_step;
        double new_y = cube->player.pos.y - sin(cube->player.angle - (90 * M_PI / 180)) * move_step;
        if (check_collision(new_x, new_y, cube->map.map))
        {
            cube->player.pos.x = new_x;
            cube->player.pos.y = new_y;
        }
	}
    // Handle rotation
    if (cube->input.left)
        cube->player.angle -= rot_step;
    if (cube->input.right)
        cube->player.angle += rot_step;

    // Ensure angle stays within [0, 2*PI]
    if (cube->player.angle < 0)
    	cube->player.angle += 2 * M_PI;
    if (cube->player.angle > 2 * M_PI)
    	cube->player.angle -= 2 * M_PI;
    return (0);
}

int game_loop(t_cube *cube)
{
    handle_movement(cube);
    calculate_ray(cube);
    return 0;
}

int	handle_mouse_move(int x, int y, t_cube *cube)
{
	(void)y;
	double	rot_step;
	int		center_x;
	int		center_y;
	
	rot_step = 0.05;
	center_x = cube->win.win_width / 2;
	center_y = cube->win.win_height / 2;
	if (x != center_x && !cube->input.c)
	{
		if (x > cube->prev_mouse_x)
			cube->player.angle += rot_step;
		else if (x < cube->prev_mouse_x)
			cube->player.angle -= rot_step;
		if (cube->player.angle < 0)
			cube->player.angle += 2 * M_PI;
		if (cube->player.angle > 2 * M_PI)
			cube->player.angle -= 2 * M_PI;
		mlx_mouse_move(cube->win.mlx_ptr, cube->win.win_ptr, center_x, center_y);
		//mlx_mouse_hide(cube->win.mlx_ptr, cube->win.win_ptr);
		cube->prev_mouse_x = center_x;
	}
	if (cube->input.c)
		mlx_mouse_show(cube->win.mlx_ptr, cube->win.win_ptr);
    return (0);
}

void	cube_init(t_cube *cube)
{
	cube->input.w = false;
    cube->input.a = false;
    cube->input.s = false;
    cube->input.d = false;
	cube->input.f = false;
	cube->input.c = false;
	cube->input.is_door = false;
	cube->player.existence = 0;
	cube->prev_mouse_x = 400;
    cube->input.left = false;
    cube->input.right = false;
	cube->win.mlx_ptr = NULL;
	cube->win.win_ptr = NULL;
	cube->map.map = NULL;
	cube->map.map_check = NULL;
	cube->map.size = NULL;
}

void cube_init2(t_cube *cube)
{
	cube->text.NO = NULL;
	cube->text.SO = NULL;
	cube->text.EA = NULL;
	cube->text.WE = NULL;
	cube->text.C = -1;
	cube->text.F = -1;
	cube->text.door = NULL;
	cube->win.win_width = 1600;
	cube->win.win_height = 900;
	cube->minimap.mini_height = 0;
	cube->minimap.mini_wid = 0;
	cube->minimap.mini_start_x = 0;
	cube->minimap.mini_start_y = 0;
	cube->map.level = 0;
	cube->inst = NULL;
}

int main(int ac, char *ag[])
{
	t_cube	cube;

	cube_init(&cube);
	cube_init2(&cube);
	if (ac != 2)
	{
		perror("ERROR\ninvalid argument");
		exit(1);
	}
	cube.win.mlx_ptr = mlx_init();
	if (parsing(&cube, ag[1]) == 1)
	{
		perror("bad parsing\n");
		on_destroy(&cube);
	}
	cube.win.win_ptr = mlx_new_window(cube.win.mlx_ptr, cube.win.win_width, cube.win.win_height, "PROVA");
	mlx_hook(cube.win.win_ptr, KeyPress, KeyPressMask, &on_keypress, &cube);
	mlx_hook(cube.win.win_ptr, KeyRelease, KeyReleaseMask, &on_keyrelease, &cube);
	mlx_hook(cube.win.win_ptr, 6, 1L << 6, handle_mouse_move, &cube);
	mlx_hook(cube.win.win_ptr, 33, 1L << 5, &on_destroy, &cube);
	mlx_loop_hook(cube.win.mlx_ptr, &game_loop, &cube);
	mlx_loop(cube.win.mlx_ptr);
	return 0;
}
