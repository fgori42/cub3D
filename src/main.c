/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:09 by fgori             #+#    #+#             */
/*   Updated: 2024/10/31 15:46:18 by aosmenaj         ###   ########.fr       */
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

//void	make_img(t_cube *cube)
//{
//	t_img *img;
	
//	img = mlx_new_image(cube->win.mlx_ptr, )	
//}

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

	if (endian == 0) {
        // Little-endian: the color is stored as BGR(A)
        color = *(int *)(pixel_data + pixel_offset);
    } else {
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

void print_ray(t_cube *cube)
{
    //int x, y;
    int ray = 0;
	int ray_width = 1;
	int num_rays =  cube->win.win_width / ray_width;
    double FOV = 60 * (M_PI / 180); // 60-degree FOV
    double angle_step = FOV / num_rays; // Angle step for each ray
    double ray_angle = cube->player.angle - (FOV / 2); // Start at the left edge of the FOV
    t_wall	*tmp;
	t_pos	pos;
	if (ray_angle < 0)
        ray_angle += 2 * M_PI;
    if (ray_angle > 2 * M_PI)
        ray_angle -= 2 * M_PI;
    while (ray < num_rays)
    {
		// Player's position
        double posX = cube->player.pos.x;
        double posY = cube->player.pos.y;

        // Ray direction based on current ray angle
        double rayDirX = cos(ray_angle);
        double rayDirY = sin(ray_angle);

        // Which box of the map we're in
        int mapX = (int)(posX);
        int mapY = (int)(posY);

        // Length of the ray from current position to the next x or y-side
        double side_dist_x;
        double side_dist_y;

        // Length of the ray from one x or y-side to the next x or y-side
        double delta_dist_x = fabs(1 / rayDirX);
        double delta_dist_y = fabs(1 / rayDirY);

		int stepX;
        int stepY;
        int hit = 0; // Has the ray hit a wall?
        int side;    // Was a NS or EW wall hit?

		if (rayDirX < 0)
        {
            stepX = -1;
            side_dist_x = (posX - mapX) * delta_dist_x;
        }
        else
        {
            stepX = 1;
            side_dist_x = ((mapX + 1.0) - posX) * delta_dist_x;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            side_dist_y = (posY - mapY) * delta_dist_y;
        }
        else
        {
            stepY = 1;
            side_dist_y = ((mapY + 1.0) - posY) * delta_dist_y;
        }
        while (!hit)
        {
			// printf("Player Position (Pixels): posX = %.2f, posY = %.2f\n", posX, posY);
			// printf("Player Position (Grid): mapX = %d, mapY = %d\n", mapX, mapY);
			// printf("Ray Direction: rayDirX = %.2f, rayDirY = %.2f\n", rayDirX, rayDirY);
			// printf("Delta Distances: delta_dist_x = %.2f, delta_dist_y = %.2f\n", delta_dist_x, delta_dist_y);
			// printf("Side Distances: side_dist_x = %.2f, side_dist_y = %.2f\n", side_dist_x, side_dist_y);
			// printf("Steps: stepX = %d, stepY = %d\n", stepX, stepY);
			// printf("Current Side: side = %d\n", side);
			// printf("Current Cell (Map): mapX = %d, mapY = %d\n\n", mapX / 64, mapY / 64);
			// sleep(1);
            // Jump to next map square, either in x-direction or y-direction
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                mapX += stepX;
                side = 0;
				cube->side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                mapY += stepY;
                side = 1;
				cube->side = 1;
            }

            // Check if the ray has hit a wall
            if (wallLoak(mapX, mapY, cube->map.map))
                hit = 1;
        }
		double hitX, hitY;
        if (side == 0)
        {
            // Vertical wall hit
            hitX = posX + side_dist_x * rayDirX;
            hitY = posY + side_dist_x * rayDirY;
        }
        else
        {
            // Horizontal wall hit
            hitX = posX + side_dist_y * rayDirX;
            hitY = posY + side_dist_y * rayDirY;
        }
		double ray_length;
		if (side == 0)
			ray_length = (mapX - posX + (1 - stepX) / 2) / rayDirX;
   		else
			ray_length = (mapY - posY + (1 - stepY) / 2) / rayDirY;
		pos.x = hitX;
		pos.y = hitY;
		tmp = ft_lstnew_cube(ray_length, &pos, ray_angle, cube);
		ft_lstadd_back_cube(&cube->inst, tmp);
        ray_angle += angle_step;
        if (ray_angle < 0)
            ray_angle += 2 * M_PI;
        if (ray_angle > 2 * M_PI)
            ray_angle -= 2 * M_PI;
        ray++;
    }
	correct_lst(cube->inst);
	int	y1;
	t_img *new_img;
	
	new_img = ft_calloc(1, sizeof(t_img));
	new_img->image = mlx_new_image(cube->win.mlx_ptr, cube->win.win_width, cube->win.win_height);
	new_img->data = mlx_get_data_addr(new_img->image, &new_img->bpp, &new_img->size_line, &new_img->format);
	cube->img = new_img;
	t_wall	*tmp_two;
	tmp = cube->inst;
	while (tmp->next)
	{
		tmp_two = cube->inst;
		y1 = 0;
		int texture_x;
		if (hit_vertical(tmp))
    		texture_x = ((int)tmp->y % 64);
		else
			texture_x = ((int)tmp->x % 64);
		while (y1 < tmp->wall_top && tmp->wall_top <= cube->win.win_height)
		{
			img_pixel_put(cube->text.C, tmp->idx, y1, &new_img);
			y1++;
		}
		y1 = tmp->wall_bottom - 1;
		while (y1 < cube->win.win_height && tmp->wall_bottom > 0)
		{
			img_pixel_put(cube->text.F, tmp->idx, y1, &new_img);
			y1++;
		}
		int wall_y = tmp->wall_top;
		if (wall_y < 0)
			wall_y = 0;
		if (tmp->wall_bottom >= cube->win.win_height)
			tmp->wall_bottom = cube->win.win_height;
		while ( wall_y < tmp->wall_bottom)
		{
			if (tmp->idx == 880)
				cube->input.dis.left_dis = tmp->ray_lenght;
			if (tmp->idx == 910)
				cube->input.dis.right_dis = tmp->ray_lenght;
			if (tmp->idx == 900)
			{
				cube->input.dis.main_dis = tmp->ray_lenght;
			}
			int texture_y = (wall_y - tmp->wall_top) * cube->texture.height / tmp->wall_height;
			if (texture_y >= cube->texture.height)
				texture_y = cube->texture.height - 1;
			// Get the color from the texture
			int color = get_texture_color(tmp->text, cube->texture.width, cube->texture.height, texture_x, texture_y);
			
				img_pixel_put(color, tmp->idx, wall_y, &new_img);
			
			wall_y++;
		}
		tmp = tmp->next;
		cube->inst = tmp;
		free(tmp_two);
	}
	draw_animation(cube);
	display_map(cube);
	mlx_put_image_to_window(cube->win.mlx_ptr, cube->win.win_ptr, new_img->image, 0, 0);
	mlx_destroy_image(cube->win.mlx_ptr, new_img->image);
	free(new_img);
}

void draw_direction(t_img *img, t_cube *cube)
{
	int tmpx;
	double ray_x, ray_y;
	double ray_length;

	ray_length = 0;
	tmpx = cube->player.pos.x;
	while (ray_length < 32)
	{
		ray_x = cube->player.pos.x + cos(cube->player.angle) * ray_length;
    	ray_y = cube->player.pos.y + sin(cube->player.angle) * ray_length;
		while ((tmpx / 64) < 32)
		{
			img_pixel_put(0x00FF00, (int)ray_x, (int)ray_y, &img);
			tmpx++;
		}
		tmpx = cube->player.pos.x;
		ray_length++;
	}
}

int     on_destroy(t_cube *cube)
{
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

void print_map(char **map) {
    // Itera finché non trovi un puntatore nullo (che indica la fine della mappa)
    for (int i = 0; map[i] != NULL; i++) {
        printf("%s\n", map[i]); // Stampa ogni riga della mappa
    }
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
	if (keysym == XK_A || keysym == XK_a)
		cube->input.a = true;
	if (keysym == XK_S || keysym == XK_s)
		cube->input.s = true;
	if (keysym == XK_D || keysym == XK_d)
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
	
	player_size = 0.5;
    // Controlla i quattro angoli del rettangolo che rappresenta il giocatore
    if (wallLoak(x - player_size, y - player_size, map) &&
        wallLoak(x + player_size, y - player_size, map) &&
        wallLoak(x - player_size, y + player_size, map) &&
        wallLoak(x + player_size, y + player_size, map))
    {
        return 0; // Collisione rilevata
    }
    return 1; // Nessuna collisione
}

int check_distance(t_cube cube, char direction)
{
	float angle;
	
	if (direction == 'a')
		angle = cube.player.angle - (90 * M_PI / 180);
	else if (direction == 'd')
		angle = cube.player.angle + (90 * M_PI / 180);
	else if (direction == 's')
		angle = cube.player.angle + (180 * M_PI / 180);
	else
		angle = cube.player.angle;
	double ray_x = cube.player.pos.x + cos(angle) * 10;
	double ray_y = cube.player.pos.y + sin(angle) * 10;
	        // Check for wall collision
    if (!check_collision(ray_x, ray_y, cube.map.map))
    	return (1);
	else
		return (0);
}

int handle_movement(t_cube *cube)
{
    double move_step = 8; // Movement speed
    double rot_step = 0.08; // Rotation speed (radians)

    // Handle forward movement
    if (cube->input.w && !check_distance(*cube, 'w') && (cube->input.dis.left_dis > 30 || cube->input.dis.right_dis > 30))
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
    // Handle player movement and drawing for the first window (cube)
    handle_movement(cube);
    print_ray(cube);
    // Handle drawing logic for the second window (cube)
    return 0;
}

int	handle_mouse_move(int x, int y, t_cube *cube)
{
	(void)y;
	double rot_step;
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
		mlx_mouse_hide(cube->win.mlx_ptr, cube->win.win_ptr);
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
	cube->prev_mouse_x = 400;
    cube->input.left = false;
    cube->input.right = false;
	cube->win.mlx_ptr = NULL;
	cube->win.win_ptr = NULL;
	cube->map.map = NULL;
	cube->map.map_check = NULL;
	cube->map.size = NULL;
	cube->text.NO = NULL;
	cube->text.SO = NULL;
	cube->text.EA = NULL;
	cube->text.WE = NULL;
	cube->text.C = -1;
	cube->text.F = -1;
	cube->text.door = NULL;
	cube->win.win_width = 1600;
	cube->win.win_height = 900;
	cube->minimap.mini_height = 64 * 5;
	cube->minimap.mini_wid = 64 * 9;
	cube->minimap.mini_start_x = 0;
	cube->minimap.mini_start_y = 0; 
	cube->map.level = 0;
	cube->inst = NULL;
}


int main(int ac, char *ag[])
{
    t_cube cube;  // Create an array of two t_cube structs
    //char *str;

    // Initialize first window (cube[0])
	cube_init(&cube);
	if (ac != 2)
	{
		perror("ERROR\ninvalid argument");
		exit(1);
	}
    cube.win.mlx_ptr = mlx_init();
	if (parsing(&cube, ag[1]) == 1)
	{
		perror("bad parsing\n");
		exit (1);
	}
    cube.win.win_ptr = mlx_new_window(cube.win.mlx_ptr, cube.win.win_width, cube.win.win_height, "PROVA");
    //// Initialize second window (cube[1])
    //// Set up hooks for input and rendering for both windows
    mlx_hook(cube.win.win_ptr, KeyPress, KeyPressMask, &on_keypress, &cube);
    mlx_hook(cube.win.win_ptr, KeyRelease, KeyReleaseMask, &on_keyrelease, &cube);
	mlx_hook(cube.win.win_ptr, 6, 1L << 6, handle_mouse_move, &cube);
	//mlx_mouse_hook(cube.win.win_ptr, MotionNotify, &cube);
    mlx_hook(cube.win.win_ptr, 33, 1L << 5, &on_destroy, &cube);
    
    //// Use a shared game loop to update both windows
    mlx_loop_hook(cube.win.mlx_ptr, &game_loop, &cube);  // Pass both cubes to the game loop as an array
    
    //// Enter the MiniLibX main loop
    mlx_loop(cube.win.mlx_ptr);

    return 0;
}	