/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majullie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 13:20:54 by majullie          #+#    #+#             */
/*   Updated: 2016/12/28 14:34:48 by majullie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		init_tab(t_env *env)
{
	size_t	i;

	if (!(env->tab = (t_vect2d**)malloc(sizeof(t_vect2d*) * env->map_w)))
		die(env, "Error");
	i = 0;
	while (i < env->map_w)
	{
		if (!(env->tab[i] = ft_memalloc(sizeof(t_vect2d) * env->map->size)))
			die(env, "Error");
		i++;
	}
}

static void		set_tab(t_env *env, int x, int y, int *line)
{
	t_vect3d			v3d;
	t_vect2d			v2d;

	v3d.x = x;
	v3d.y = -y;
	v3d.z = -line[x];
	v2d.x = env->scale * (((sqrt(2) / 2) * (v3d.x - v3d.y)));
	v2d.y = env->h_factor * env->scale
		* ((0.82 * v3d.z - ((1. / sqrt(6) * (v3d.x + v3d.y)))));
	env->tab[x][y].x = v2d.x;
	env->tab[x][y].y = v2d.y;
	env->min_x = (env->min_x < v2d.x) ? env->min_x : v2d.x;
	env->min_y = (env->min_y < v2d.y) ? env->min_y : v2d.y;
	env->max_x = (env->max_x > v2d.x) ? env->max_x : v2d.x;
	env->max_y = (env->max_y > v2d.y) ? env->max_y : v2d.y;
}

void			map_to_2d(t_env *env)
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
