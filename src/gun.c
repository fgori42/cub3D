

#include "cube.h"

void	plus_imgins(t_img *src, int startX, int startY, t_cube *cube)
{
	int		color;
	char	*pixel_dest;
	int		y;
	int		x;
	int		orig_startY;

	orig_startY = startY;
	x = 0;
	while (x <  cube->minimap.mini_wid)
	{
		startY = orig_startY;
		y = 0;
		while (y++ <  cube->minimap.mini_height)
		{
			color = get_texture_color(src, 64, 64, x, y);
			pixel_dest = (cube->img)->data + ((startY * (cube->img)->size_line) + (startX * (cube->img)->bpp / 8));
			if (color != 0x00000000)
			{
				*(int *)pixel_dest = color;
			}
			startY++;
		}
		startX++;
		x++;
	}
}


void	fire_ball(t_cube *cube)
{
	//t_img		*ball;
	static int	sec;

	if (cube->input.f == false)
		return ;
	sec++;
	if (sec == 30)
	{
		//ball = ft_calloc(1, sizeof(t_img));
		//ball->image = mlx_new_image(cube->win.mlx_ptr, sec, sec);
		//ball->data = mlx_get_data_addr(ball->image, &ball->bpp, &ball->size_line, &ball->format);
		//plus_img()
		plus_imgins(cube->text.fire, 0, 0, cube);
		//mlx_destroy_image(cube->win.mlx_ptr, ball->image);
		//free(ball);
		cube->input.f = false;
	}
}
