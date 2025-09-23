/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:10 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/23 16:36:26 by mel-houa         ###   ########.fr       */
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
int parse_map(t_game *game, int fd,char *filedata);



// ======================= rander part ===============================

// for window 
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WIN_TITLE "CUB3D"
// use xev for check this coorect number of esc key
#define ESC_KEY 65307


// struct for creat image 
typedef struct s_image
{  
    void *img_ptr;
    int bits_per_pexile;
    int size_line;
    int endian;
    char *img_pex_ptr;
}   t_img;

int handle_key(int key, void *pram);
int handle_win_close(void *param);

#endif