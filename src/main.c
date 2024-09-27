/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosmenaj <aosmenaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:09 by fgori             #+#    #+#             */
/*   Updated: 2024/09/27 17:59:30 by aosmenaj         ###   ########.fr       */
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
    double ray_step = 5; // Adjust for how far to step along the ray

    // Start from the player's position
    x = cube->player.pos->x;
    y = cube->player.pos->y;

    // Loop until the ray reaches a maximum distance or hits a wall
    while (ray_length < MAX_DISTANCE)
    {
        // Calculate the ray's x and y coordinates
        ray_x = x + cos(ray_angle) * ray_length;
        ray_y = y + sin(ray_angle) * ray_length;

        // Check for wall collision
        if (!wallLoak(ray_x, ray_y, cube->map.map))
        {
            // Draw the ray at the intersection point
            mlx_pixel_put(cube->win.mlx_ptr, cube->win.win_ptr, (int)ray_x, (int)ray_y, 0x00520a);
            break; // Exit loop after hitting a wall
        }

        // Increment the ray length
        ray_length += ray_step - 1;
    }
}

void draw_player(int x, int y, t_cube *cube)
{
	int j;
	int i;
	int tmpx;

	i = 0;
	tmpx = x;
	while (i < 64)
	{
		j = 0;
		while(j < 64)
		{
			mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr, x, y,  0xff0202);
			j++;
			x++;
		}
		x = tmpx;
		i++;
		y++;
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
                draw_square(x * 64, y * 64, 0x000000, cube); // Use correct offset for squares
            else 
                draw_square(x * 64, y * 64, 0xd8d8d8, cube);
            x++; // Move to the next column
        }
		draw_player(cube->player.pos->x, cube->player.pos->y, cube);
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
			// if (pos.x / 64 == (CentInSis(cube->player.pos->x)) && ((float)y + (pos.y / 100)) == CentInSis(cube->player.pos->y))
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
			//else if (x == cube->player.pos->x && y == cube->player.pos->y)
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
					mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr,pos.x, j,   0xd8d8d8);
				}
				pos.y = 1;
			}
			y++;
		}
		if ((int)pos.x % 64 == 0)
			x++;
		draw_player(cube->player.pos->x, cube->player.pos->y, cube);
		print_ray(cube);
	}
	return(0);
}
//pos.x / 64 == cube->player.pos->x && ((float)y + (pos.y / 100)) == cube->player.pos->y

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
	if (keysym == XK_W || keysym == XK_w || keysym == XK_Up)
		if (wallLoak(cube->player.pos->x,cube->player.pos->y - 64, cube->map.map))
			cube->player.pos->y -= 64;
	if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
		if (wallLoak(cube->player.pos->x,cube->player.pos->y + 64, cube->map.map))
			cube->player.pos->y += 64;
	if (keysym == XK_D || keysym == XK_d || keysym == XK_Right)
		if (wallLoak(cube->player.pos->x + 64,cube->player.pos->y, cube->map.map))
			cube->player.pos->x += 64;
	if (keysym == XK_A || keysym == XK_a || keysym == XK_Left)
		if (wallLoak(cube->player.pos->x - 64,cube->player.pos->y, cube->map.map))
			cube->player.pos->x -= 64;
	if (keysym == XK_Escape)
	{
		on_destroy(&cube->win);
	}
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

int main()
{
	t_cube	cube;
	char *str;
	
	cube.win.mlx_ptr = mlx_init();
	cube.win.win_ptr = mlx_new_window(cube.win.mlx_ptr, 512, 512, "PROVA");
	cube.player.pos->x = 64;
	cube.player.pos->y = 64;
	cube.player.angle = 90;
	str = gnl();
	cube.map.map = ft_split( str, '\n');
	mlx_loop_hook(cube.win.mlx_ptr, &draw, &cube);
	mlx_key_hook(cube.win.win_ptr, &on_keypress, &cube);
	mlx_hook(cube.win.win_ptr, 33, 1L << 5, &on_destroy, &cube);
	mlx_loop(cube.win.mlx_ptr);
}	