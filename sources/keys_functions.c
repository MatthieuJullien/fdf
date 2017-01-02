/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majullie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 13:57:04 by majullie          #+#    #+#             */
/*   Updated: 2016/12/28 14:09:25 by majullie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		move(t_env *env, int dx, int dy)
{
	env->img->x0 += dx;
	env->img->y0 += dy;
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->image, env->img->x0,
			env->img->y0);
}

static void		scale_map(t_env *env, int scale)
{
	if (scale < 0)
	{
		env->scale -= 10;
		if (env->scale < 10)
			env->scale = 10;
	}
	else
	{
		env->scale += 10;
		if (env->scale > 50)
			env->scale = 50;
	}
	free_tab(env);
	map_to_2d(env);
	reposition_map(env);
	mlx_destroy_window(env->mlx, env->win);
	env->win = mlx_new_window(env->mlx, env->width, env->height, TITLE);
	draw(env);
	mlx_key_hook(env->win, handle_keys, env);
}

static void		scale_height(t_env *env, int scale)
{
	if (scale < 0)
	{
		env->h_factor -= 0.2;
		if (env->h_factor < 0.2)
			env->h_factor = 0.2;
	}
	else
	{
		env->h_factor += 0.2;
		if (env->h_factor > 1.4)
			env->h_factor = 1.4;
	}
	free_tab(env);
	map_to_2d(env);
	reposition_map(env);
	draw(env);
	mlx_key_hook(env->win, handle_keys, env);
}

int				handle_keys(int keycode, t_env *env)
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
	else if (keycode == 24)
		scale_map(env, 1);
	else if (keycode == 27)
		scale_map(env, -1);
	else if (keycode == 116)
		scale_height(env, 1);
	else if (keycode == 121)
		scale_height(env, -1);
	return (1);
}
