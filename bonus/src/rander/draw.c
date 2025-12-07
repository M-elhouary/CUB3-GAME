/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:09 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/03 15:57:30 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

typedef struct s_draw
{
	int		screen_x;
	int		wall_height;
	int		start_y;
	int		end_y;
	int		y;
	double	ray_x;
	double	ray_y;
	double	distance;
	double	t;
	double	correct_dist;
	// textute cordinates
	int		tex_x;
	int		tex_y;
	double	tex_step;
	double	tex_pos;
}			t_draw_vars;

t_texture	*side_hit(t_ray_hit *hit, double ray_y, double ray_x, t_game *game)
{
	char	hit_char;

	hit_char = game->map->map_arr[hit->map_y][hit->map_x];
	if (hit_char == 'D')
	{
		return (&game->textures[4]);
	}
	else
	{
		if (hit->side == 1 && ray_y < 0)
			return (&game->textures[0]);
		else if (hit->side == 1 && ray_y > 0)
			return (&game->textures[1]);
		else if (hit->side == 0 && ray_x < 0)
			return (&game->textures[2]);
		else
			return (&game->textures[3]);
	}
	return (NULL);
}
void tex_cordinates(t_texture *texture, t_ray_hit hit, t_game *game,
					t_draw_vars *vars)
{
	if (vars->wall_height <= 0 || texture->height <= 0)
	{
		vars->tex_x = 0;
		vars->tex_y = 0;
		vars->tex_step = 0.0;
		vars->tex_pos = 0.0;
		return;
	}
	vars->tex_x = (int)(hit.wall_x * (double)texture->width);
	if ((hit.side == 0 && vars->ray_x > 0) || (hit.side == 1 && vars->ray_y < 0))
		vars->tex_x = texture->width - vars->tex_x - 1;
	if (vars->tex_x < 0)
		vars->tex_x = 0;
	if (vars->tex_x >= texture->width)
		vars->tex_x = texture->width - 1;
	vars->tex_step = (double)texture->height / (double)vars->wall_height;
	vars->tex_pos = ((double)vars->start_y - (double)game->scren_height / 2.0 + (double)vars->wall_height / 2.0) * vars->tex_step;
}

void draw_verical_line(t_draw_vars *vars, t_texture *texture, t_img *img)
{
	unsigned int color;

	while (vars->y < vars->end_y)
	{
		vars->tex_y = (int)vars->tex_pos;
		if (vars->tex_y >= texture->height)
			vars->tex_y = texture->height - 1;
		if (vars->tex_y < 0)
			vars->tex_y = 0;

		vars->tex_pos += vars->tex_step;
		color = get_texture_color(texture, vars->tex_x, vars->tex_y);
		put_pixel(vars->screen_x, vars->y, img, color);
		vars->y++;
	}
}

void calcule_dist_wall_height(t_game *game, t_draw_vars *vars, t_ray_hit hit)
{
	vars->wall_height = (int)(game->scren_height / hit.distance);
	vars->start_y = (game->scren_height - vars->wall_height) / 2;
	if (vars->start_y < 0)
		vars->start_y = 0;
	vars->end_y = vars->start_y + vars->wall_height;
	if (vars->end_y >= game->scren_height)
		vars->end_y = game->scren_height - 1;
}

int	draw(t_game *game, t_img *img)
{
	t_draw_vars	vars;
	t_ray_hit	hit;
	t_texture	*texture;
	double		camera_x;

	draw_ceiling_and_floor(game, img);
	vars.screen_x = 0;
	while (vars.screen_x < game->scren_width)
	{
		camera_x = 2 * (double)vars.screen_x / (double)game->scren_width - 1;
		vars.ray_x = game->player.dir_x + game->player.plane_x * camera_x;
		vars.ray_y = game->player.dir_y + game->player.plane_y * camera_x;
		hit = cast_ray(game, vars.ray_x, vars.ray_y);
		calcule_dist_wall_height(game, &vars, hit);
		texture = side_hit(&hit, vars.ray_y, vars.ray_x, game);
		if (texture == NULL)
			return (0);
		tex_cordinates(texture, hit, game, &vars);
		vars.y = vars.start_y;
		draw_verical_line(&vars, texture, img);
		vars.screen_x++;
	}
	mini_map(game, game->img);
	mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
	return (0);
}
