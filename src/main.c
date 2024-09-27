/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:09 by fgori             #+#    #+#             */
/*   Updated: 2024/09/27 21:56:41 by aosmenaj         ###   ########.fr       */
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

void print_ray(t_cube *cube)
{
    int x, y;
    double ray_angle = cube->player.angle; // Angle of the ray
    double ray_length = 0;
    double ray_x, ray_y;
    double ray_step = 1; // Adjust for how far to step along the ray

    // Start from the player's position
    x = cube->player.pos.x;
    y = cube->player.pos.y;

    // Loop until the ray reaches a maximum distance or hits a wall
    while (ray_length < MAX_DISTANCE)
    {
        // Calculate the ray's x and y coordinates
        ray_x = x + cos(ray_angle) * ray_length;
        ray_y = y + sin(ray_angle) * ray_length;

        // Check for wall collision
        if (!wallLoak(ray_x, ray_y, cube->map.map))
			break;
            // Draw the ray at the intersection point
        mlx_pixel_put(cube->win.mlx_ptr, cube->win.win_ptr, (int)ray_x, (int)ray_y, 0xff0202);

        // Increment the ray length
        ray_length += ray_step;
    }
	cube->texture.height = (64 * (512 / 2)) / ray_length;
}

void draw_player(int x, int y, t_cube *cube)
{
	// int j;
	// int i;
	// int tmpx;

	// i = 0;
	// tmpx = x;
	// while (i < 64)
	// {
	// 	j = 0;
	// 	while(j < 64)
	// 	{
			mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr, x, y,  0xff0202);
	// 		j++;
	// 		x++;
	// 	}
	// 	x = tmpx;
	// 	i++;
	// 	y++;
	// }
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
			{
				mlx_put_image_to_window(cube->win.mlx_ptr
				, cube->win.win_ptr
				, cube->texture.img
				, x * 64
				, y * 64);
			}
            else 
                draw_square(x * 64, y * 64, 0xd8d8d8, cube);
            x++; // Move to the next column
        }
		draw_player(cube->player.pos.x, cube->player.pos.y, cube);
		print_ray(cube);
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
		print_ray(cube);
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
    double move_step = 2.0; // Movement speed
    double rot_step = 0.03; // Rotation speed (radians)

    // Handle forward/backward movement
    if (cube->input.w && wallLoak(cube->player.pos.x, cube->player.pos.y - move_step, cube->map.map))
        cube->player.pos.y -= move_step;
    if (cube->input.s && wallLoak(cube->player.pos.x, cube->player.pos.y + move_step, cube->map.map))
        cube->player.pos.y += move_step;

    // Handle left/right movement (strafing)
    if (cube->input.a && wallLoak(cube->player.pos.x - move_step, cube->player.pos.y, cube->map.map))
        cube->player.pos.x -= move_step;
    if (cube->input.d && wallLoak(cube->player.pos.x + move_step, cube->player.pos.y, cube->map.map))
        cube->player.pos.x += move_step;

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

    // Handle player movement
    handle_movement(cube);

    // Redraw the scene
    draw(cube);

    return 0;
}

int main()
{
	t_cube	cube;
	char *str;
	cube.input.w = false;
    cube.input.a = false;
    cube.input.s = false;
    cube.input.d = false;
    cube.input.left = false;
    cube.input.right = false;
	
	cube.win.mlx_ptr = mlx_init();
	cube.win.win_ptr = mlx_new_window(cube.win.mlx_ptr, 512, 512, "PROVA");
	cube.texture.height = 64;
	cube.texture.width = 64;
	cube.player.pos.x = 94;
	cube.player.pos.y = 94;
	cube.texture.img = mlx_xpm_file_to_image(cube.win.mlx_ptr, "textures/wall.xpm", &cube.texture.height, &cube.texture.width);
	if (!cube.texture.img)
	{
		printf("fanculo\n");
		exit(1);
	}
	cube.player.angle = 90 * (M_PI / 180);
	str = gnl();
	cube.map.map = ft_split( str, '\n');
	
	// Set up key press and release hooks
	mlx_hook(cube.win.win_ptr, KeyPress, KeyPressMask, &on_keypress, &cube);
	mlx_hook(cube.win.win_ptr, KeyRelease, KeyReleaseMask, &on_keyrelease, &cube);

	
	// Render the game
	mlx_loop_hook(cube.win.mlx_ptr, &game_loop, &cube);
	mlx_hook(cube.win.win_ptr, 33, 1L << 5, &on_destroy, &cube);

	mlx_loop(cube.win.mlx_ptr);
}	