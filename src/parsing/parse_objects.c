/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:00:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/19 20:32:37 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Helper function to convert string to object type
*/
static t_object_type	parse_object_type(char *type_str)
{
	if (ft_strcmp(type_str, "door") == 0)
		return (OBJ_DOOR);
	else if (ft_strcmp(type_str, "health") == 0)
		return (OBJ_HEALTH);
	else if (ft_strcmp(type_str, "ammo") == 0)
		return (OBJ_AMMO);
	else if (ft_strcmp(type_str, "key") == 0)
		return (OBJ_KEY);
	else if (ft_strcmp(type_str, "enemy") == 0)
		return (OBJ_ENEMY);
	else if (ft_strcmp(type_str, "switch") == 0)
		return (OBJ_SWITCH);
	return (OBJ_DOOR);
}

/*
** Parse OBJECT line from map file
** Format: OBJECT <type> <x> <y> <texture_path> [state] [param]
** Examples:
**   OBJECT door 3 2 textures/door.xpm closed
**   OBJECT health 2 3 textures/health.xpm 25
**   OBJECT ammo 5 5 textures/ammo.xpm 30
**   OBJECT enemy 4 4 textures/enemy.xpm patrol
*/
static int	parse_object_line(t_game *game, char *line)
{
	char			**parts;
	t_object		*obj;
	t_object_type	type;
	double			x;
	double			y;

	parts = ft_split(line, ' ');
	if (!parts || ft_strlen_2d(parts) < 5)
		return (printf("Error\nInvalid object definition\n"), 0);
	type = parse_object_type(parts[1]);
	if (ft_strcmp(parts[1], "unknown") == 0)
		return (printf("Error\nUnknown object type: %s\n", parts[1]), 0);
	if (!is_all_digits(parts[2]) || !is_all_digits(parts[3]))
		return (printf("Error\nObject coordinates must be numeric\n"), 0);
	x = ft_atoi(parts[2]) + 0.5;
	y = ft_atoi(parts[3]) + 0.5;
	obj = create_object(type, x, y, parts[4]);
	if (!obj)
		return (0);
	if (!add_object(game, obj))
	{
		free(obj);
		return (0);
	}
	return (1);
}

/*
** Process object definitions from map file
** Objects are defined after the map data
*/
int	parse_objects(t_game *game, int fd, char *first_line)
{
	char	*line;
	char	*trimmed;

	(void)first_line;
	line = get_line(fd);
	while (line != NULL)
	{
		trimmed = ft_strtrim(line, " \n\t");
		if (trimmed && trimmed[0] != '\0' && ft_strncmp(trimmed, "OBJECT", 6) == 0)
		{
			if (!parse_object_line(game, trimmed))
			{
				free(trimmed);
				free(line);
				return (0);
			}
		}
		free(trimmed);
		free(line);
		line = get_line(fd);
	}
	return (1);
}

/*
** Create a new object with given parameters
*/
t_object	*create_object(t_object_type type, double x, double y, char *texture)
{
	t_object	*obj;

	if (!texture)
		return (NULL);
	obj = (t_object *)ft_malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->pos_x = x;
	obj->pos_y = y;
	obj->texture_path = ft_strdup(texture);
	if (!obj->texture_path)
		return (free(obj), NULL);
	obj->state = DOOR_CLOSED;
	obj->health = 0;
	obj->ammo_count = 0;
	obj->key_id = 0;
	obj->scale = 1.0;
	obj->visible = 1;
	obj->next = NULL;
	return (obj);
}

/*
** Add object to the game's object linked list
*/
int	add_object(t_game *game, t_object *obj)
{
	t_object	*current;

	if (!game || !obj)
		return (0);
	if (game->object_count >= MAX_OBJECTS)
		return (printf("Error\nMax objects (%d) exceeded\n", MAX_OBJECTS), 0);
	if (!game->objects)
	{
		game->objects = obj;
	}
	else
	{
		current = game->objects;
		while (current->next)
			current = current->next;
		current->next = obj;
	}
	game->object_count++;
	return (1);
}
