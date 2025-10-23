/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:10 by moirhira          #+#    #+#             */
/*   Updated: 2025/10/23 22:20:47 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define key_down    65364
#define key_up      65362
#define key_left    65361
#define key_right   65363
#define ESC_KEY     65307
#define WIN_TITLE  "CUB3D"

# include "../libraries/get_next_line/get_next_line.h"
# include "../libraries/libft/libft.h"
# include "/usr/include/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>


typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
    int left_arrow;
    int right_arrow;
    int esc;
}   t_keys;


typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
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

typedef struct s_img
{
    void *img_ptr;
    int  bit_per_pixel;
    int  size_line;
    int  endian;
    char *img_pex_ptr;
}t_img;


typedef struct s_game {
    void *mlx;
    void *win;
    int win_width;
    int win_height;
    t_map *map;
    t_img *img;
    t_player player;
    t_color floor_color;
    t_color ceiling_color;
    char *tex_paths[4];
    t_keys keys;
    double move_speed;
    double rot_speed;
}   t_game;



//==============================================


// func of randring part
int ft_init_randring(t_img *image, t_game *game);
int draw(t_game *game, t_img *img);
int move(t_game *game);



//===============================================




// parse.c
int	parse(t_game *game, char *filedata);

// parse_color_and_texture.c
int	validate_file_extension(char *file, char *extension);
int parse_texture(char *path, char **dest);
int parse_color(char *path, t_color *dest);

// parse_map.c
int parse_map(t_game *game, int fd, char *first_line);

//validate_map.c
int	validate_map(t_game *game);

// parsing_utils.c
int	is_dir(char *arg);
int is_all_digits(char *str);
int ft_isempty(char *str);
int	is_player(char c);
int close_and_free(t_game *game);
#endif