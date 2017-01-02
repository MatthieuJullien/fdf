/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majullie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 14:00:27 by majullie          #+#    #+#             */
/*   Updated: 2017/01/02 13:37:09 by majullie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include <stdio.h>

# define TITLE "FdF"
# define DEFAULT_W 500
# define DEFAULT_H 500

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
	float			scale;
	int				min_x;
	int				min_y;
	int				max_x;
	int				max_y;
	int				width;
	int				height;
	float			h_factor;
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

void				die(t_env *env, char *msg);
void				free_env(t_env *env);
void				free_tab(t_env *env);
void				get_map(char *filename, t_env *env);
void				map_to_2d(t_env *env);
void				print_map(t_env *env);
void				draw(t_env *env);
void				reposition_map(t_env *env);
int					handle_keys(int keycode, t_env *env);

#endif
