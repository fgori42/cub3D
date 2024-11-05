

#include "cube.h"

void draw_image(t_img *bg, t_img *img, int start_x, int start_y)
{
	int y;
	int x;

	y = 0;
    while (y < img->height)
	{
        x = 0;
        while (x < img->width) 
		{
            int bg_x = start_x + x;
            int bg_y = start_y + y;
            int gun_pixel = get_texture_color(img->image, x, y);
            if (gun_pixel != 0x00FFFFFF)
            	img_pixel_put(gun_pixel, bg_x, bg_y, &bg);
            x++;
        }
        y++;
    }
}

void take_frame(t_cube *cube, char *path_image, t_img *bg)
{
	t_img *img;

	img = ft_calloc(1, sizeof(t_img));
	img->image = mlx_xpm_file_to_image(cube->win.mlx_ptr, path_image, &img->width, &img->height);

	int start_x = cube->win.win_width - img->width;
	int start_y = cube->win.win_height - img->height;
	
	draw_image(bg, img, start_x, start_y);
	mlx_destroy_image(cube->win.mlx_ptr, img->image);
	free(img);
}

void draw_animation(t_cube *cube)
{
	static int time;
	char *frames[5];

	frames[0] = "./textures/gun1.xpm";
	frames[1] = "./textures/gun2.xpm";
	frames[2] = "./textures/gun3.xpm";
	frames[3] = "./textures/gun4.xpm";
	frames[4] = "./textures/gun5.xpm";

	if (cube->input.f == false)
		take_frame(cube, frames[0], cube->img);
	else
	{
		if (time >= 0 && time < 2)
			take_frame(cube, frames[1], cube->img);
		else if (time >= 2 && time < 4)
			take_frame(cube, frames[2], cube->img);
		else if (time >= 4 && time < 6)
			take_frame(cube, frames[3], cube->img);
		else if (time >= 6 && time < 8)
			take_frame(cube, frames[4], cube->img);
		else if (time >= 8)
		{
			take_frame(cube, frames[0], cube->img);
			time = 0;
			cube->input.f = false;
			if (cube->input.is_door)
				cube->map.map[(int)cube->input.dor.y][(int)cube->input.dor.x] = 'd';
			return ;
		}
		time++;
	}
}

