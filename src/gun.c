

#include "cube.h"

void	fire_ball(t_cube *cube)
{
	t_img		*ball;
	static int	sec;

	if (cube->input.f == false)
		return ;
	sec++;
	printf("sec = %d", sec);
	if (sec == 300)
	{
		ball = ft_calloc(1, sizeof(t_img));
		ball->image = mlx_new_image(cube->win.mlx_ptr, sec, sec);
		ball->data = mlx_get_data_addr(ball->image, &ball->bpp, &ball->size_line, &ball->format);
		//plus_img()
		plus_img(cube->text.fire, sec, sec, cube);
		mlx_destroy_image(cube->win.mlx_ptr, ball->image);
		free(ball);
	}
}
