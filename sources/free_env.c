/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majullie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 13:39:47 by majullie          #+#    #+#             */
/*   Updated: 2017/01/02 10:34:30 by majullie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		free_tab(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->map_w)
	{
		free(env->tab[i]);
		i++;
	}
}

void		free_env(t_env *env)
{
	if (env->tab)
		free_tab(env);
	if (env->image)
		mlx_destroy_image(env->mlx, env->image);
	if (env->img)
		free(env->img);
	if (env->tab)
		free(env->tab);
	if (env->map)
		ft_llist_destroy(&env->map);
}
