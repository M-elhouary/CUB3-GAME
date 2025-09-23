/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:10 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/23 10:19:20 by moirhira         ###   ########.fr       */
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
	int		width;
	int		height;
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

// parse_color_and_texture.c
int	validate_file_extension(char *file);
int parse_texture(char *path, char **dest);
int parse_color(char *path, t_color *dest);

// parse_map.c
int parse_map(t_game *game, int fd);

//validate_map.c
int	validate_map(t_game *game);

// parsing_utils.c
int ft_isempty(char *str);
#endif