/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majullie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 13:17:48 by majullie          #+#    #+#             */
/*   Updated: 2017/01/02 13:45:06 by majullie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		get_nb_num(char *line)
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

static void		fill_tab(t_env *env, int *tab, char *line)
{
	size_t	i;

	i = 0;
	while (i < env->map_w && *line != '\0')
	{
		tab[i] = ft_atoi(line);
		while (*line != '\0' && *line != ' ')
			line++;
		while (*line == ' ')
			line++;
		i++;
	}
}

void			get_map(char *filename, t_env *env)
{
	int		fd;
	char	*line;
	int		*tab;
	int		ret;

	ft_llist_create(&env->map);
	if ((fd = open(filename, O_RDONLY)) == -1 || env->map == NULL)
		die(env, "Error");
	if (get_next_line(fd, &line) == -1)
		die(env, "Error");
	env->map_w = get_nb_num(line);


	//env->scale = 500 / env->map_w;
	env->scale = 0.01;

	tab = (int*)malloc(env->map_w * sizeof(int));
	fill_tab(env, tab, line);
	ft_llist_add_last(env->map, tab, env->map_w * sizeof(int));
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			die(env, "Error");
		tab = (int*)malloc(env->map_w * sizeof(int));
		fill_tab(env, tab, line);
		ft_llist_add_last(env->map, tab, env->map_w * sizeof(int));
	}
	if (close(fd) == -1)
		die(env, "Error");
}
