/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:00:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/19 20:32:37 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Free all objects in the linked list
*/
void	free_objects(t_object *objects)
{
	t_object	*current;
	t_object	*next;

	current = objects;
	while (current)
	{
		next = current->next;
		if (current->texture_path)
			free(current->texture_path);
		free(current);
		current = next;
	}
}

/*
** Calculate distance from player to object using Euclidean distance
*/
double	get_object_distance(t_game *game, t_object *obj)
{
	double	dx;
	double	dy;

	if (!game || !obj)
		return (9999.0);
	dx = game->player.pos_x - obj->pos_x;
	dy = game->player.pos_y - obj->pos_y;
	return (sqrt(dx * dx + dy * dy));
}

/*
** Check if coordinates collide with an object
** Objects with state != 0 (like open doors) don't block movement
*/
int	object_collision(t_game *game, double x, double y)
{
	t_object	*current;
	double		dist;

	if (!game)
		return (0);
	current = game->objects;
	while (current)
	{
		if (!current->visible)
		{
			current = current->next;
			continue ;
		}
		dist = sqrt((x - current->pos_x) * (x - current->pos_x) +
				(y - current->pos_y) * (y - current->pos_y));
		if (dist < 0.3)
		{
			/* Doors don't collide when open */
			if (current->type == OBJ_DOOR && current->state == DOOR_OPEN)
			{
				current = current->next;
				continue ;
			}
			return (1);
		}
		current = current->next;
	}
	return (0);
}

/*
** Bubble sort objects by distance from player (furthest first for rendering)
** This ensures correct depth sorting when rendering sprites
*/
void	sort_objects_by_distance(t_object **objects, t_game *game)
{
	t_object	*current;
	t_object	*next;
	t_object	temp;
	int			swapped;

	if (!objects || !*objects)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *objects;
		while (current && current->next)
		{
			next = current->next;
			if (get_object_distance(game, current) < get_object_distance(game, next))
			{
				temp = *current;
				*current = *next;
				*next = temp;
				current->next = next;
				next->next = temp.next;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

/*
** Handle object interaction (E key)
** Currently supports doors and pickups
*/
void	handle_object_interaction(t_game *game, t_object *obj)
{
	double	dist;

	if (!game || !obj)
		return ;
	dist = get_object_distance(game, obj);
	if (dist > OBJECT_DISTANCE)
		return ;
	if (obj->type == OBJ_DOOR)
	{
		if (obj->state == DOOR_CLOSED)
			obj->state = DOOR_OPENING;
		else if (obj->state == DOOR_OPEN)
			obj->state = DOOR_CLOSING;
	}
	else if (obj->type == OBJ_HEALTH && obj->visible)
	{
		obj->visible = 0;
	}
	else if (obj->type == OBJ_AMMO && obj->visible)
	{
		obj->visible = 0;
	}
	else if (obj->type == OBJ_KEY && obj->visible)
	{
		obj->visible = 0;
	}
}

/*
** Check if player is near any interactable object and can interact
*/
void	check_object_interaction(t_game *game)
{
	t_object	*current;
	double		dist;

	if (!game || game->interaction_cooldown > 0)
	{
		if (game->interaction_cooldown > 0)
			game->interaction_cooldown--;
		return ;
	}
	current = game->objects;
	while (current)
	{
		if (current->visible)
		{
			dist = get_object_distance(game, current);
			if (dist < OBJECT_DISTANCE)
			{
				handle_object_interaction(game, current);
				game->interaction_cooldown = 10;
				break ;
			}
		}
		current = current->next;
	}
}

/*
** Update all objects (animate doors, update states, etc)
*/
void	update_objects(t_game *game)
{
	t_object	*current;

	if (!game)
		return ;
	current = game->objects;
	while (current)
	{
		if (current->type == OBJ_DOOR)
		{
			if (current->state == DOOR_OPENING)
				current->state = DOOR_OPEN;
			else if (current->state == DOOR_CLOSING)
				current->state = DOOR_CLOSED;
		}
		current = current->next;
	}
}

/*
** Load texture for an object from file
*/
int	load_object_texture(t_object *obj, void *mlx)
{
	int	fd;

	if (!obj || !obj->texture_path || !mlx)
		return (0);
	fd = open(obj->texture_path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCannot open object texture: %s\n",
				obj->texture_path), 0);
	close(fd);
	obj->texture.img_ptr = mlx_xpm_file_to_image(mlx, obj->texture_path,
			&obj->texture.width, &obj->texture.height);
	if (!obj->texture.img_ptr)
		return (printf("Error\nFailed to load object texture: %s\n",
				obj->texture_path), 0);
	obj->texture.addr = mlx_get_data_addr(obj->texture.img_ptr,
			&obj->texture.bits_per_pixel, &obj->texture.size_line,
			&obj->texture.endian);
	if (!obj->texture.addr)
		return (0);
	return (1);
}
