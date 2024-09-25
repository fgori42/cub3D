/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:23:09 by fgori             #+#    #+#             */
/*   Updated: 2024/09/25 16:59:57 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

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

int put_game (t_cube *cube)
{
	int x = 0;
	int y = 0;
	int j = 0;
	t_pos pos = {0};

	while (pos.x++ < size_mtx('x', cube->map.map) * 64)
	{
		y = 0;
		j = 0;
		while(cube->map.map[y])
		{
			if (cube->map.map[y][x] == '1')
			{
				while(pos.y++ < 64)
				{
					j++;	
					mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr,pos.x, j,  0xFFFFFF);	
				}
				pos.y = 0;
			}
			else if (x == cube->player.pos->x && y == cube->player.pos->y)
			{
				while(pos.y++ < 64)
				{
					j++;
					mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr,pos.x, j,   0xFF0000);
				}
				pos.y = 0;
			}
			else 
			{
				while(pos.y++ < 64)
				{
					j++;
					mlx_pixel_put(cube->win.mlx_ptr,cube->win.win_ptr,pos.x, j,   0xC0C0C0);
				}
				pos.y = 0;
			}
			y++;
		}
		if ((int)pos.x % 64 == 0)
			x++;
	}
	return(0);
}

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
		cube->player.pos->y -= 1;
	if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
		cube->player.pos->y += 1;
	if (keysym == XK_D || keysym == XK_d || keysym == XK_Right)
		cube->player.pos->x += 1;;
	if (keysym == XK_A || keysym == XK_a || keysym == XK_Left)
		cube->player.pos->x -= 1;;
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
	cube.win.win_ptr = mlx_new_window(cube.win.mlx_ptr, 500, 500, "PROVA");
	cube.player.pos->x = 2;
	cube.player.pos->y = 2;
	str = gnl();
	cube.map.map = ft_split( str, '\n');
	mlx_key_hook(cube.win.win_ptr, &on_keypress, &cube);
	mlx_hook(cube.win.win_ptr, 33, 1L << 5, &on_destroy, &cube);
	mlx_loop_hook(cube.win.mlx_ptr, put_game, &cube);
	mlx_loop(cube.win.mlx_ptr);
}	