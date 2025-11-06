/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:10 by moirhira          #+#    #+#             */
/*   Updated: 2025/11/06 21:00:34 by mel-houa         ###   ########.fr       */
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
# include <unistd.h>
# include <X11/keysym.h>
#include <math.h>


typedef struct s_player
{
    double pos_x;
    double pos_y;
    char dir;

    // added by rendering part
    int dir_x; 
    int dir_y;
    double plane_x;
    double plane_y;
    double ray_dir_x;
    double ray_dir_y;
} t_player;


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


typedef struct s_image
{
    void *img_ptr;
    int  bit_per_pixel;
    int  size_line;
    int  endian;
    char *img_pex_ptr;
}   t_img;


typedef struct s_game 
{
    void    *mlx;
    void    *win;
    int		scren_width;
	int		scren_height;
    char    *tex_paths[4];
    t_map   *map;
    t_player player;
    t_color floor_color;
    t_img    *img;
    t_color ceiling_color;
    t_keys keys;
    double move_speed;
    double rot_speed;
}   t_game;

// ================================================ randring ============================================================


#define key_down    65364
#define key_up      65362
#define key_left    65361
#define key_right   65363
#define ESC_KEY     65307
#define WIN_TITLE  "L3AKS"



// func of randring part
int draw(t_game *game, t_img *img);
void win_scal(t_game *game);
int move(t_game *game);
void camera(t_game *game);
int is_wall(t_game *game, double x, double y);
double cast_ray(t_game *game, double ray_x, double ray_y);
void put_pixel(int x, int y, t_img *img, int color);
int mini_map(t_game *game, t_img *img);
int handle_key(int key, void *param);
int handle_win_close(void *param);
void draw_player(t_img *img, t_game *game, double x, double y);


int key_press_handler(int keycode, t_game *game);
int key_release_handler(int keycode, t_game *game);
void init_keys(t_game *game);
void move_player(t_game *game);
void rotate_player(t_game *game);
int game_update(t_game *game);
int init_randring(t_game *game);



// =============================================================================================================================

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