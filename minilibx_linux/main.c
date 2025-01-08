#include "mlx.h"
#include <stdio.h>

int	main(void)
{
	void	*mlx;
	char	*img;
	void	*mlx_win;
	char	*relative_path = "../bonus/imgs/marsmap1k.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);
	mlx_loop(mlx);
}

