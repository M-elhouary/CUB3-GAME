/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:10 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/12 12:29:22 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/get_line/get_line.h"
# include "../libraries/libft/libft.h"
# include "/usr/include/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY_DOWN 65364
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define ESC_KEY 65307
# define WIN_TITLE "CUB3D"

typedef struct s_ray_hit
{
	double		distance;
	double		wall_x;
	int			side;
	int			map_x;
	int			map_y;
}				t_ray_hit;

typedef struct s_texture
{
	void		*img_ptr;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	char		dir;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		ray_dir_x;
	double		ray_dir_y;
}				t_player;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			e;
	int			left_arrow;
	int			right_arrow;
	int			esc;
}				t_keys;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			hex_color;
}				t_color;

typedef struct s_map
{
	char		**map_arr;
	int			width;
	int			height;
}				t_map;

typedef struct s_image
{
	void		*img_ptr;
	int			bit_per_pixel;
	int			size_line;
	int			endian;
	char		*img_pex_ptr;
}				t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			scren_width;
	int			scren_height;
	char		*tex_paths[5];
	t_map		*map;
	t_player	player;
	t_color		floor_color;
	t_img		*img;
	t_color		ceiling_color;
	t_keys		keys;
	t_texture	textures[5];
	double		move_speed;
	double		rot_speed;
}				t_game;

int				draw(t_game *game, t_img *img);
void			draw_ceiling_and_floor(t_game *game, t_img *img);
void			camera(t_game *game);
int				is_wall(t_game *game, double x, double y);
void			put_pixel(int x, int y, t_img *img, int color);
t_ray_hit		cast_ray(t_game *game, double ray_x, double ray_y);
int				mini_map(t_game *game, t_img *img);
void			draw_player(t_img *img, t_game *game, double x, double y);
int				key_press_handler(int keycode, t_game *game);
int				key_release_handler(int keycode, t_game *game);
void			move_player(t_game *game);
void			rotate_player(t_game *game, double rot, int f);
void			apply_rotation(t_game *game, double rot_speed);
void			open_door(t_game *game);
int				game_update(t_game *game);
int				init_randring(t_game *game);
unsigned int	get_texture_color(t_texture *texture, int tex_x, int tex_y);
int				load_all_textures(t_game *game);

int				parse(t_game *game, char *filedata);
int				process_config_line(t_game *game, char *trimmed, int *parsed);
void			strip_newline(char *line);
int				validate_file_extension(char *file, char *extension);
int				parse_texture(char *path, char **dest);
int				parse_color(char *path, t_color *dest);
int				parse_map(t_game *game, int fd, char *first_line);
int				validate_map(t_game *game);
int				check_map_is_closed(t_game *game);
int				is_dir(char *arg);
int				is_all_digits(char *str);
int				ft_isempty(char *str);
int				is_player(char c);
int				close_and_free(t_game *game);

#endif