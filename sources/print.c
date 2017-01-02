/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majullie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 13:46:31 by majullie          #+#    #+#             */
/*   Updated: 2017/01/02 13:41:47 by majullie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		pixel_put(t_env *env, int x1, int y1)
{
	int			pixel;

	if (x1 >= 1000 || y1 >= 1000)
		return ;
	pixel = y1 * env->img->sz_line + x1 * env->img->bpp / 8;
	env->img->mem[pixel] = (unsigned char)env->color;
	env->img->mem[pixel + 1] = (unsigned char)(env->color >> 8);
	env->img->mem[pixel + 2] = (unsigned char)(env->color >> 16);
	env->img->mem[pixel + 3] = (unsigned char)(env->color >> 24);
}

static void		print_segment2(t_segment segment, t_env *env, int dx, int dy)
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

//printf("print pixel A %d,%d\n", segment.x1, segment.y1);
		pixel_put(env, segment.x1, segment.y1);
		if (segment.x1 == segment.x2 && segment.y1 == segment.y2)
			break ;
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

static void		print_segment(t_env *env, t_vect2d v1, t_vect2d v2)
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

void			print_map(t_env *env)
{
printf("print map debut\n");
	size_t			i;
	size_t			j;


	j = 0;
	while (j < env->map->size)
	{
		i = 0;
		while (i < env->map_w)
		{

//printf("print map map->size=%zu\n", env->map->size);
//printf("print map map_w=%zu\n", env->map_w);
			if (i < env->map_w - 1 && i < 1000)
				print_segment(env, env->tab[i][j], env->tab[i + 1][j]);
			if (j < env->map->size - 1)
				print_segment(env, env->tab[i][j], env->tab[i][j + 1]);
			i++;
		}
		j++;
	}
}

void			draw(t_env *env)
{
	env->img->x0 = 0;
	env->img->y0 = 0;
	env->image = mlx_new_image(env->mlx, env->width, env->height);
	env->img->mem = mlx_get_data_addr(env->image, &env->img->bpp,
			&env->img->sz_line, &env->img->endian);
	print_map(env);
	mlx_put_image_to_window(env->mlx, env->win, env->image, env->img->x0,
			env->img->y0);

printf("scale = %f\n", env->scale);


}
