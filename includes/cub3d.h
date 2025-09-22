/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:10 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/22 14:06:52 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../libraries/get_next_line/get_next_line.h"
# include "../libraries/libft/libft.h"
# include "/usr/include/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_player
{
    double x;
    double y;
} t_player;

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;
typedef struct s_map
{
	char	**map_arr;
	int		rows;
	int		cols;
}			t_map;

typedef struct s_game {
    void *mlx;
    void *win;
    t_map *map;
    t_player player;
    t_color floor_color;
    t_color ceiling_color;
    char *tex_paths[4];
}   t_game;


// parse.c
int	parse(t_game *game, char *filedata);
#endif