#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "mlx.h"

typedef struct		s_image
{
	char			*mem;
	int				x0;
	int				y0;
	int				bpp;
	int				sz_line;
	int				endian;
}					t_image;

typedef struct		s_vect2d
{
	int				x;
	int				y;
}					t_vect2d;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*image;
	t_image			*img;
	t_llist			*map;
	size_t			map_w;
	t_vect2d		**tab;
	unsigned int	color;
	int				scale;
	int				min_x;
	int				min_y;
}					t_env;

typedef struct		s_segment
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
}					t_segment;

typedef struct		s_vect3d
{
	int				x;
	int				y;
	int				z;
}					t_vect3d;

void		die(char *msg);
void		scale_map(t_env *env, int scale);

#endif
