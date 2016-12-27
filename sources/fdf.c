#include "fdf.h"

#include <stdio.h>

/*
   static int		get_keycode(int keycode, void *param)
   {
   param = NULL;
   printf("%d\n", keycode);
   return (1);
   }
   */

void		free_tab(t_env *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < env->map_w)
	{
		j = 0;
		while (j < env->map->size)
		{
			free(env->tab[i] + j);
			j++;
		}
		i++;
	}
}

void		print_tab(t_env *env)
{
	size_t x;
	size_t y;

	y= 0;
	while (y < env->map->size)
	{
		x = 0;
		while (x < env->map_w)
		{
			printf("%d,%d ", env->tab[x][y].x, env->tab[x][y].y);
			x++;
		}
		printf("\n");
		y++;
	}
}

void			free_env(t_env *env)
{
//	free_tab(env);
//	mlx_destroy_image(env->mlx, env->image);
	free(env->img);
	free(env->tab);
	ft_llist_destroy(&env->map);
	free(env);
}

void		move(t_env *env, int dx, int dy)
{
	env->img->x0 += dx;
	env->img->y0 += dy;
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->image, env->img->x0,
			env->img->y0);
}

static int		handle_keys(int keycode, t_env *env)
{
	if (keycode == 53)
	{
		free_env(env);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 126)
		move(env, 0, -20);
	else if (keycode == 125)
		move(env, 0, 20);
	else if (keycode == 124)
		move(env, 20, 0);
	else if (keycode == 123)
		move(env, -20, 0);
	return (1);
}



void			pixel_put(t_env *env, int x1, int y1)
{
	int			pixel;

	pixel = y1 * env->img->sz_line + x1 * env->img->bpp / 8;
	env->img->mem[pixel] = (unsigned char)env->color;
	env->img->mem[pixel + 1] = (unsigned char)(env->color >> 8);
	env->img->mem[pixel + 2] = (unsigned char)(env->color >> 16);
	env->img->mem[pixel + 3] = (unsigned char)(env->color >> 24);
}



static void		print_segment2(t_segment segment,  t_env *env, int dx, int dy)
{
	int		incx;
	int		incy;
	int		err;
	int		e2;

	incx = segment.x1 < segment.x2 ? 1 : -1;
	incy = segment.y1 < segment.y2 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		pixel_put(env, segment.x1, segment.y1);
		if (segment.x1 == segment.x2 && segment.y1 == segment.y2)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			segment.x1 += incx;
		}
		if (e2 < dy)
		{
			err += dx;
			segment.y1 += incy;
		}
	}
}

void		print_segment(t_env *env, t_vect2d v1, t_vect2d v2)
{
	t_segment	segment;
	int			dx;
	int			dy;

	segment.x1 = v1.x;
	segment.y1 = v1.y;
	segment.x2 = v2.x;
	segment.y2 = v2.y;
	dx = ABS(v2.x - v1.x);
	dy = ABS(v2.y - v1.y);
	print_segment2(segment, env, dx, dy);
}

void		print_map(t_env *env)
{
	size_t			i;
	size_t			j;

	j = 0;
	while (j < env->map->size)
	{
		i = 0;
		while (i < env->map_w)
		{
			if (i < env->map_w - 1)
				print_segment(env, env->tab[i][j], env->tab[i + 1][j]);
			if (j < env->map->size - 1)
				print_segment(env, env->tab[i][j], env->tab[i][j + 1]);
			i++;
		}
		j++;
	}
}

void		draw(t_env *env)
{
	env->img = ft_memalloc(sizeof(t_image));
	env->image = mlx_new_image(env->mlx, 500, 500);
	env->img->mem = mlx_get_data_addr(env->image, &env->img->bpp,
			&env->img->sz_line,	&env->img->endian);
	print_map(env);
	mlx_put_image_to_window(env->mlx, env->win, env->image, env->img->x0,
			env->img->y0);

}

void		init_tab(t_env *env)
{
	size_t	i;

	if (!(env->tab = (t_vect2d**)malloc(sizeof(t_vect2d*) * env->map_w)))
		die("Error");
	i = 0;
	while (i < env->map_w)
	{
		if (!(env->tab[i] = ft_memalloc(sizeof(t_vect2d) * env->map->size)))
			die("Error");
		i++;
	}
}

void		set_tab(t_env *env, int x, int y, int *line)
{
	t_vect3d			v3d;
	t_vect2d			v2d;

	v3d.x = x;
	v3d.y = y;
	v3d.z = line[x];
	v2d.x = env->scale * (((sqrt(2) / 2) * (v3d.x - v3d.y)));
	v2d.y = env->scale * ((0.82 * v3d.z - ((1. / sqrt(6) * (v3d.x + v3d.y)))));
	env->tab[x][y].x = v2d.x;
	env->tab[x][y].y = v2d.y;

	env->min_x = (env->min_x < v2d.x) ? env->min_x : v2d.x;
	env->min_y = (env->min_y < v2d.y) ? env->min_y : v2d.y;
}

void		map_to_2d(t_env *env)
{
	t_llnode			*cur;
	int					*line;
	size_t				x;
	size_t				y;

	init_tab(env);


	cur = env->map->first;
	y = 0;
	while (cur != NULL)
	{
		line = (int*)cur->val;
		x = 0;
		while (x < env->map_w)
		{
			set_tab(env, x, y, line);
			x++;
		}
		y++;
		cur = cur->next;
	}
}
void		die(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int			get_nb_num(char *line)
{
	int		nb_num;
	char	prev;

	nb_num = 0;
	prev = ' ';
	while (*line != '\0')
	{
		if (!ft_isdigit(prev) && ft_isdigit(*line))
			nb_num++;
		prev = *line;
		line++;
	}
	return (nb_num);
}

void		fill_tab(int *tab, char *line)
{
	int		i;

	i = 0;
	while (*line != '\0')
	{
		tab[i] = ft_atoi(line);
		while (*line != '\0' && *line != ' ')
			line++;
		while (*line == ' ')
			line++;
		i++;
	}
}

void		get_map(char *filename, t_env *env)
{
	int		fd;
	char	*line;
	int		*tab;
	int		ret;

	ft_llist_create(&env->map);
	if ((fd = open(filename, O_RDONLY)) == -1 || env->map == NULL)
		die("Error");
	if (get_next_line(fd, &line) == -1)
		die("Error");
	env->map_w = get_nb_num(line);
	tab = (int*)malloc(env->map_w * sizeof(int));
	fill_tab(tab, line);
	ft_llist_add_last(env->map, tab, env->map_w * sizeof(int));
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			die("Error");
		tab = (int*)malloc(env->map_w * sizeof(int));
		fill_tab(tab, line);

		ft_llist_add_last(env->map, tab, env->map_w * sizeof(int));
	}
	if (close(fd) == -1)
		die("Error");

	t_llnode *cur = env->map->first;
	int	*iline;
	size_t i;
	while (cur != NULL)
	{
		iline = (int*)cur->val;
		i = 0;
		while (i < env->map_w)
		{
			printf("%2d ", iline[i]);
			i++;
		}
		printf("\n");
		cur = cur->next;
	}

}

void		reposition_map(t_env *env)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < env->map->size)
	{
		x = 0;
		while (x < env->map_w)
		{
			env->tab[x][y].x -= env->min_x;
			env->tab[x][y].y -= env->min_y;
			x++;
		}
		y++;
	}
}


int			main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
	{
		ft_putendl("Usage : ./fdf <filename>");
		return (EXIT_SUCCESS);
	}


//puts("ERROR1");

	env.scale = 10;
	get_map(argv[1], &env);

//puts("ERROR2");

	map_to_2d(&env);

//puts("ERROR3");

	reposition_map(&env);

//puts("ERROR4");

	env.mlx = mlx_init();
	if (!(env.win = mlx_new_window(env.mlx, 500, 500, "FdF")))
		die("Error");
	env.color = 0x00FFFFFF;


//puts("ERROR5");
	draw(&env);


//puts("ERROR6");
	mlx_key_hook(env.win, handle_keys, &env);
	//mlx_key_hook(env.win, get_keycode, &env);
	mlx_loop(env.mlx);
	return (EXIT_FAILURE);
}
