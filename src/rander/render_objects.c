/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:00:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/20 00:24:36 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Draw a filled rectangle on the image buffer (for simple sprite rendering)
*/
static void	draw_rect(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	if (!img || !img->img_pex_ptr)
		return ;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if ((x + j >= 0 && x + j < 1920) &&
				(y + i >= 0 && y + i < 1080))
				put_pixel(x + j, y + i, img, color);
			j++;
		}
		i++;
	}
}

/*
** Calculate billboard position for object using raycasting
** This projects a 3D position onto the 2D screen
*/
static void	calculate_billboard(t_game *game, t_object *obj,
		double *screen_x, double *screen_y, double *size)
{
	double	relative_x;
	double	relative_y;
	double	distance;
	double	camera_plane_dist;

	if (!game || !obj || !screen_x || !screen_y || !size)
		return ;
	relative_x = obj->pos_x - game->player.pos_x;
	relative_y = obj->pos_y - game->player.pos_y;
	distance = sqrt(relative_x * relative_x + relative_y * relative_y);
	if (distance < 0.1)
		distance = 0.1;
	*size = (game->scren_height / distance) * 0.5;
	camera_plane_dist = atan2(relative_y, relative_x) - 
		atan2(game->player.dir_y, game->player.dir_x);
	while (camera_plane_dist > M_PI)
		camera_plane_dist -= 2 * M_PI;
	while (camera_plane_dist < -M_PI)
		camera_plane_dist += 2 * M_PI;
	*screen_x = game->scren_width / 2 + (camera_plane_dist / (M_PI / 3.0)) * 
		(game->scren_width / 2.0);
	*screen_y = game->scren_height / 2;
}

/*
** Render a single object sprite with billboarding
** Sprites always face the camera
*/
static void	render_object_sprite(t_game *game, t_img *img, t_object *obj)
{
	double	screen_x;
	double	screen_y;
	double	size;
	int		color;
	int		start_x;
	int		start_y;

	if (!game || !img || !obj || !obj->visible)
		return ;
	calculate_billboard(game, obj, &screen_x, &screen_y, &size);
	if (size < 1.0)
		return ;
	start_x = (int)(screen_x - size / 2);
	start_y = (int)(screen_y - size / 2);
	/* Draw object based on type */
	if (obj->type == OBJ_DOOR)
	{
		if (obj->state == DOOR_CLOSED)
			color = 0xFF4400;
		else
			color = 0x00AA00;
	}
	else if (obj->type == OBJ_HEALTH)
		color = 0xFF0000;
	else if (obj->type == OBJ_AMMO)
		color = 0xFFFF00;
	else if (obj->type == OBJ_KEY)
		color = 0x00FFFF;
	else if (obj->type == OBJ_ENEMY)
	{
		/* Different colors for different enemy types */
		if (obj->enemy_type == ENEMY_SNIPER)
			color = 0xFF00FF;  /* Magenta for sniper */
		else if (obj->enemy_type == ENEMY_RUSHER)
			color = 0xFF0000;  /* Red for rusher */
		else if (obj->enemy_type == ENEMY_SUPPORT)
			color = 0x0000FF;  /* Blue for support */
		else if (obj->enemy_type == ENEMY_MELEE)
			color = 0xFF6600;  /* Orange for melee */
		else
			color = 0xFF00FF;  /* Magenta default */
	}
	else
		color = 0xFFFFFF;
	draw_rect(img, start_x, start_y, (int)size, color);
}

/*
** Render all objects in the game with proper depth sorting
** Furthest objects rendered first (painter's algorithm)
*/
void	render_objects(t_game *game, t_img *img)
{
	t_object	*current;

	if (!game || !img || !game->objects)
		return ;
	sort_objects_by_distance(&game->objects, game);
	current = game->objects;
	while (current)
	{
		if (current->visible)
			render_object_sprite(game, img, current);
		current = current->next;
	}
}
