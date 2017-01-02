/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majullie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:00:36 by majullie          #+#    #+#             */
/*   Updated: 2017/01/02 12:12:06 by majullie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		die(t_env *env, char *msg)
{
	free_env(env);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
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
			env->width = env->max_x - env->min_x + 50;
			if (env->width < 0 || env->width > 1000)
				env->width = 1000;
			env->height = env->max_y - env->min_y + 50;
			if (env->height < 0 || env->height > 1000)
				env->height = 1000;
			x++;
		}
		y++;
	}
}

static void	init_env(t_env *env)
{
	env->scale = 10;
	env->h_factor = 1.;
	env->min_x = DEFAULT_W;
	env->min_y = DEFAULT_H;
	env->max_x = 0;
	env->max_y = 0;
	env->color = 0x00FFFFFF;
	env->image = NULL;
}

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
	{
		ft_putendl("Usage : ./fdf <filename>");
		return (EXIT_SUCCESS);
	}
	init_env(&env);
	get_map(argv[1], &env);
	map_to_2d(&env);
	reposition_map(&env);
	env.mlx = mlx_init();
printf("ERROR1\n");
printf("w %d h %d\n", env.width, env.height);
	if (!(env.win = mlx_new_window(env.mlx, env.width, env.height, TITLE)))
		die(&env, "Error");
	if (!(env.img = (t_image*)malloc(sizeof(t_image))))
		die(&env, "Error");
printf("ERROR2\n");
	draw(&env);
printf("ERROR3\n");
printf("ERROR4\n");
	mlx_key_hook(env.win, handle_keys, &env);
	mlx_loop(env.mlx);
	return (EXIT_FAILURE);
}
