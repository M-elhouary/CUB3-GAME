/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:10:09 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/19 23:28:16 by mel-houa         ###   ########.fr       */
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

// Determine which texture to use based on which side was hit
t_texture	*side_hit(int hit_side, double ray_y, double ray_x, t_game *game)
{
	
	if (hit_side == 1 && ray_y < 0)
		return (&game->textures[0]);
	else if (hit_side == 1 && ray_y > 0)
		return (&game->textures[1]);
	else if (hit_side == 0 && ray_x < 0)
		return (&game->textures[2]);
	else
		return (&game->textures[3]);
	return (NULL);
}
// Calculate the x-coordinate on the texture
void	tex_cordinates(t_texture *texture, t_ray_hit hit, t_game *game,
		t_draw_vars *vars)
{
	if (vars->wall_height <= 0 || texture->height <= 0)
	{
		vars->tex_x = 0;
		vars->tex_y = 0;
		vars->tex_step = 0.0;
		vars->tex_pos = 0.0;
		return ;
	}
	vars->tex_x = (int)(hit.wall_x * (double)texture->width);
	if (vars->tex_x < 0)
		vars->tex_x = 0;
	if (vars->tex_x >= texture->width)
		vars->tex_x = texture->width - 1;
	vars->tex_step = (double)texture->height / (double)vars->wall_height;
	vars->tex_pos = ((double)vars->start_y - (double)game->scren_height / 2.0
			+ (double)vars->wall_height / 2.0) * vars->tex_step;
}

//  Draw the vertical line at this screen column
void	draw_verical_line(t_draw_vars *vars, t_texture *texture, t_img *img)
{
	unsigned int	color;

	while (vars->y < vars->end_y)
	{
		// 4. Get the y-coordinate on the texture and get the color.
		vars->tex_y = (int)vars->tex_pos;
		vars->tex_pos += vars->tex_step;
		color = get_texture_color(texture, vars->tex_x, vars->tex_y);
		put_pixel(vars->screen_x, vars->y, img, color);
		vars->y++;
	}
}

// 'camera_x' maps the screen column to the range [-1, 1] for a correct FOV.

void	calcule_dist_wall_height(t_game *game, t_draw_vars *vars, t_ray_hit hit)
{
	// FIX Correct for Fisheye Distortion
	//  This math corrects the distance to prevent walls from looking curved.
	vars->correct_dist = hit.distance * (vars->ray_x * game->player.dir_x
			+ vars->ray_y * game->player.dir_y);
	// Calculate wall height based on the CORRECTED distance
	vars->wall_height = (int)(game->scren_height / vars->correct_dist);
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
		// 'camera_x' maps the screen column to the range [-1,1] for a correct FOV.
		camera_x = 2 * (double)vars.screen_x / (double)game->scren_width - 1;
		vars.ray_x = game->player.dir_x + game->player.plane_x * camera_x;
		vars.ray_y = game->player.dir_y + game->player.plane_y * camera_x;
		// Cast the ray using our upgraded function
		hit = cast_ray(game, vars.ray_x, vars.ray_y);
		calcule_dist_wall_height(game, &vars, hit);
		texture = side_hit(hit.side, vars.ray_y, vars.ray_x, game);
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
