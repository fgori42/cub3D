/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:09 by fgori             #+#    #+#             */
/*   Updated: 2024/09/28 18:33:04 by aosmenaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

#define MAX_DISTANCE sqrt((512 * 512) + (512 * 512))

//void print_map(char **map)
//{
//    int x = 0;
//    int y = 0;

//    while (map[y] != NULL) // Scorre le righe finché non trova una riga vuota (NULL)
//    {
//        x = 0;
//        while (map[y][x] != '\0') // Scorre i caratteri della riga finché non trova il terminatore di stringa
//        {
//            printf("%c", map[y][x]); // Stampa il carattere corrente
//            x++;
//        }
//        printf("\n"); // Va a capo alla fine della riga
//        y++;
//    }
//}
bool	wallLoak(int x, int y, char **map)
{
	x /= 64;
	y /= 64;
	
    // Return whether the position is a wall or not
    return (map[y][x] != '1');
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

int draw_wall_3d(void *param)
{
	t_cube *cube = (t_cube *)param;
	int x = 0;
	int y = 0;
	int map_width = size_mtx('x', cube->map.map); // Get width of the map
    int map_height = size_mtx('y', cube->map.map); // Get height of the map
	while (y < map_height) // Iterate over rows
    {
        x = 0; // Reset x for each row
        while (x < map_width) // Iterate over columns
        {
            if (cube->map.map[y][x] == '1')
				mlx_put_image_to_window(cube->win.mlx_ptr, cube->win.win_ptr, cube->texture.img, x * 64, y * 64);
            else 
                draw_square(x * 64, y * 64, 0xd8d8d8, cube);
            x++; // Move to the next column
        }
		y++;
	}
	return (1);
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

void print_ray(t_cube *cube, t_cube *cube2)
{
    int x, y;
    int ray = 0;
    double ray_length = 0;
    double ray_x, ray_y;
    double ray_step = 0.05; // Adjust for how far to step along the ray
    int wall_height;
    int wall_top, wall_bottom;
    int screen_height = 512;
	int screen_width = 512;
	int ray_width = 2;
	int num_rays =  screen_width / ray_width;
	
    double FOV = 30 * (M_PI / 180); // 60-degree FOV
    double angle_step = FOV / num_rays; // Angle step for each ray
    double ray_angle = cube->player.angle - (FOV / 2); // Start at the left edge of the FOV
    if (ray_angle < 0)
        ray_angle += 2 * M_PI;
    if (ray_angle > 2 * M_PI)
        ray_angle -= 2 * M_PI;

    // Start from the player's position
    x = cube->player.pos.x;
    y = cube->player.pos.y;

	int map_size = size_mtx('x', cube->map.map) * size_mtx('y', cube->map.map); // Get height of the map
    while (ray < num_rays)
    {
        while (ray_length < MAX_DISTANCE)
        {
            // Calculate the ray's x and y coordinates
            ray_x = x + cos(ray_angle) * ray_length;
            ray_y = y + sin(ray_angle) * ray_length;

            // Check for wall collision
            if (!wallLoak(ray_x, ray_y, cube->map.map))
                break;
			mlx_pixel_put(cube->win.mlx_ptr, cube->win.win_ptr, (int)ray_x, (int)ray_y, 0xff0202);
            // Increment the ray length
            ray_length += ray_step;
        }

        if (ray_length > 0)
        {
			double new_angle = ray_angle - cube->player.angle;
			 if (new_angle < 0)
            	new_angle += 2 * M_PI;
        	if (new_angle > 2 * M_PI)
            	new_angle -= 2 * M_PI;
			ray_length = ray_length * cos(new_angle);
            // Adjust wall height based on distance (simple perspective correction)
            wall_height = (int)((screen_height * map_size) / ray_length - 10);
			if (wall_height > 512)
				wall_height = 512;

            // Calculate the top and bottom positions of the wall slice on the screen
            wall_top = (screen_height / 2) - (wall_height / 2);
            wall_bottom = (screen_height / 2) + (wall_height / 2);

            // Clamp the values to avoid drawing outside the screen
            if (wall_top < 0) 
				wall_top = 0;
            if (wall_bottom >= screen_height) 
				wall_bottom = screen_height - 1;

            // Calculate texture_x based on where the ray hit the wall
            int texture_x = (int)((ray_x - (int)ray_x) * cube2->texture.width);
			
            int y1 = 0;
			while (y1 < wall_bottom)
			{
				mlx_pixel_put(cube2->win.mlx_ptr, cube2->win.win_ptr, ray * ray_width, y1, 0x38285c);
                y1++;
			}
			y1 = wall_bottom;
			while (y1 <= 512)
			{
				mlx_pixel_put(cube2->win.mlx_ptr, cube2->win.win_ptr, ray * ray_width, y1, 0x17ff00);
                y1++;
			}
			int wall_y = wall_top;
            while (wall_y < wall_bottom)
            {
                // Map screen y to texture y
                int texture_y = (wall_y - wall_top) * cube2->texture.height / wall_height;

                // Get the color from the texture
                int color = get_texture_color(cube2->texture.img, cube2->texture.width, cube2->texture.height, texture_x, texture_y);
                // Draw the pixel on the screen
                mlx_pixel_put(cube2->win.mlx_ptr, cube2->win.win_ptr, ray * ray_width, wall_y, color);

                // Move to the next pixel
                wall_y++;
            }
        }
        ray_length = 0;
        ray_angle += angle_step;
        if (ray_angle < 0)
            ray_angle += 2 * M_PI;
        if (ray_angle > 2 * M_PI)
            ray_angle -= 2 * M_PI;

        ray++;
    }
}

void draw_player(int x, int y, t_cube *cube)
{
	int i;
	int tmpx;
	double ray_x, ray_y;
	double ray_length;

	ray_length = 0;
	i = 0;
	tmpx = x;
	while (ray_length < 32)
	{
		ray_x = x + cos(cube->player.angle) * ray_length;
    	ray_y = y + sin(cube->player.angle) * ray_length;
		while ((x / 64) < 30)
		{
			mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr, ray_x, ray_y,  0x000000);
			x++;
		}
		x = tmpx;
		ray_length++;
	}
}
// Function to draw a square (cube in 2D)
void draw_square(int x, int y, int color, t_cube *cube) {
    int i, j;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 64; j++) {
            mlx_pixel_put(cube->win.mlx_ptr, cube->win.win_ptr, x + j, y + i, color);
        }
    }
}

int draw(t_cube *cube)
{
	int x;
	int y;

	t_cube *cube2 = &cube[1]; // Access the second cube structure
	cube->texture.height = 64;
    cube->texture.width = 64;
    cube->texture.img = mlx_xpm_file_to_image(cube[0].win.mlx_ptr, "textures/wall.xpm", &cube[0].texture.height, &cube[0].texture.width);
	x = 0;
	y = 0;
	int map_width = size_mtx('x', cube->map.map); // Get width of the map
    int map_height = size_mtx('y', cube->map.map); // Get height of the map
	while (y < map_height) // Iterate over rows
    {
        x = 0; // Reset x for each row
        while (x < map_width) // Iterate over columns
        {
            if (cube->map.map[y][x] == '1')
				mlx_put_image_to_window(cube->win.mlx_ptr, cube->win.win_ptr, cube->texture.img, x * 64, y * 64);
            else 
                draw_square(x * 64, y * 64, 0xd8d8d8, cube);
            x++; // Move to the next column
        }
		draw_player(cube->player.pos.x, cube->player.pos.y, cube);
		print_ray(cube, cube2);
        y++; // Move to the next row
    }
    return (1);
}

int put_game (t_cube *cube)
{
	int x = 0;
	int y = 0;
	int j = 0;
	t_pos pos = {0};

	while (pos.x < size_mtx('x', cube->map.map) * 64)
	{
		pos.x++;
		y = 0;
		j = 0;
		while(cube->map.map[y])
		{
			// if (pos.x / 64 == (CentInSis(cube->player.pos.x)) && ((float)y + (pos.y / 100)) == CentInSis(cube->player.pos.y))
			// 	mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr,pos.x, j,   0xFF0000);
			if (cube->map.map[y][x] == '1')
			{
				while(pos.y++ <= 64)
				{
					j++;
					mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr,pos.x, j,  0x000000);	
				}
				pos.y = 1;
			}
			//else if (x == cube->player.pos.x && y == cube->player.pos.y)
			//{
			//	//while(pos.y++ < 4)
			//	//{
			//	//	j++;
			//	//	mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr,pos.x, j,   0xFF0000);
			//	//}
			//	while(pos.y++ < 64)
			//	{
			//		j++;
			//		mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr,pos.x, j,   0xFF0000);
			//	}
			//	pos.y = 0;
			//}
			else 
			{
				while(pos.y++ <= 64)
				{
					j++;
					mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr,pos.x, j, 0xd8d8d8);
				}
				pos.y = 1;
			}
			y++;
		}
		if ((int)pos.x % 64 == 0)
			x++;
		draw_player(cube->player.pos.x, cube->player.pos.y, cube);
	}
	return(0);
}
//pos.x / 64 == cube->player.pos.x && ((float)y + (pos.y / 100)) == cube->player.pos.y

int     on_destroy(t_win *win)
{
        if (win->win_ptr)
                mlx_destroy_window(win-> mlx_ptr, win->win_ptr);
        if (win->mlx_ptr)
        {
            mlx_destroy_display(win->mlx_ptr);
            free(win->mlx_ptr);
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
	if (keysym == XK_Left)
		cube->input.left = true;
	if (keysym == XK_Right)
		cube->input.right = true;
	if (keysym == XK_Escape)
		on_destroy(&cube->win);
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
	if (keysym == XK_Left)
		cube->input.left = false;
	if (keysym == XK_Right)
		cube->input.right = false;
	return (0);
}

int handle_movement(t_cube *cube)
{
    double move_step = 10; // Movement speed
    double rot_step = 0.2; // Rotation speed (radians)

    // Handle forward movement
    if (cube->input.w) {
        double new_x = cube->player.pos.x + cos(cube->player.angle) * move_step;
        double new_y = cube->player.pos.y + sin(cube->player.angle) * move_step;
        if (wallLoak(new_x, new_y, cube->map.map))
        {
            cube->player.pos.x = new_x;
            cube->player.pos.y = new_y;
        }
    }

    // Handle backward movement
    if (cube->input.s) {
        double new_x = cube->player.pos.x - cos(cube->player.angle) * move_step;
        double new_y = cube->player.pos.y - sin(cube->player.angle) * move_step;
        if (wallLoak(new_x, new_y, cube->map.map))
        {
            cube->player.pos.x = new_x;
            cube->player.pos.y = new_y;
        }
    }

   // Handle left/right movement (strafing)
    if (cube->input.a && wallLoak(cube->player.pos.x + move_step, cube->player.pos.y, cube->map.map))
        cube->player.pos.x += move_step;
    if (cube->input.d && wallLoak(cube->player.pos.x - move_step, cube->player.pos.y, cube->map.map))
        cube->player.pos.x -= move_step;
		
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

char *gnl(void)
{
	int fd;
	char *str;
	
	fd = open("map",  O_RDWR );
	if (fd < 0)
		return (NULL);
	str = ft_calloc(5000, 1);
	read(fd, str, 5000);
	//printf("%s\n",str);
	return(str);
}

int game_loop(void *param)
{
    t_cube *cube = (t_cube *)param;

    // Handle player movement and drawing for the first window (cube)
    handle_movement(cube);
    draw(cube);
    // Handle drawing logic for the second window (cube2)
    return 0;
}

int main()
{
    t_cube cube[2];  // Create an array of two t_cube structs
    char *str;

    // Initialize first window (cube[0])
    cube[0].input.w = false;
    cube[0].input.a = false;
    cube[0].input.s = false;
    cube[0].input.d = false;
    cube[0].input.left = false;
    cube[0].input.right = false;
    
    cube[0].win.mlx_ptr = mlx_init();
    cube[0].win.win_ptr = mlx_new_window(cube[0].win.mlx_ptr, 512, 512, "PROVA");
	cube[0].texture.height = 64;
    cube[0].texture.width = 64;
    cube[0].player.pos.x = 160;
    cube[0].player.pos.y = 160;
    cube[0].texture.img = mlx_xpm_file_to_image(cube[0].win.mlx_ptr, "textures/wall.xpm", &cube[0].texture.height, &cube[0].texture.width);
    cube[0].player.angle = 90 * (M_PI / 180);
    str = gnl();
    cube[0].map.map = ft_split(str, '\n');

    // Initialize second window (cube[1])
    cube[1].win.mlx_ptr = cube[0].win.mlx_ptr; // Use the same mlx_ptr
    cube[1].win.win_ptr = mlx_new_window(cube[1].win.mlx_ptr, 512, 512, "GAMEE");
    cube[1].texture.height = 64;
    cube[1].texture.width = 64;
    cube[1].texture.img = mlx_xpm_file_to_image(cube[1].win.mlx_ptr, "textures/wall.xpm", &cube[1].texture.height, &cube[1].texture.width);

    // Set up hooks for input and rendering for both windows
    mlx_hook(cube[0].win.win_ptr, KeyPress, KeyPressMask, &on_keypress, &cube[0]);
    mlx_hook(cube[0].win.win_ptr, KeyRelease, KeyReleaseMask, &on_keyrelease, &cube[0]);

    mlx_hook(cube[1].win.win_ptr, 33, 1L << 5, &on_destroy, &cube[1]);
    
    // Use a shared game loop to update both windows
    mlx_loop_hook(cube[0].win.mlx_ptr, &game_loop, cube);  // Pass both cubes to the game loop as an array
    
    // Enter the MiniLibX main loop
    mlx_loop(cube[0].win.mlx_ptr);

    return 0;
}	