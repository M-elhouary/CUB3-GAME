/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configurations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:40:00 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/23 16:22:16 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*get_arg(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (&line[i]);
}

static int	handle_texture_line(t_game *game, char *trimmed)
{
	if (ft_strncmp("NO ", trimmed, 3) == 0)
		return (parse_texture(get_arg(trimmed), &game->tex_paths[0]));
	if (ft_strncmp("SO ", trimmed, 3) == 0)
		return (parse_texture(get_arg(trimmed), &game->tex_paths[1]));
	if (ft_strncmp("WE ", trimmed, 3) == 0)
		return (parse_texture(get_arg(trimmed), &game->tex_paths[2]));
	if (ft_strncmp("EA ", trimmed, 3) == 0)
		return (parse_texture(get_arg(trimmed), &game->tex_paths[3]));
	return (-1);
}

static int	handle_color_line(t_game *game, char *trimmed)
{
	if (ft_strncmp("F ", trimmed, 2) == 0)
		return (parse_color(get_arg(trimmed), &game->floor_color));
	if (ft_strncmp("C ", trimmed, 2) == 0)
		return (parse_color(get_arg(trimmed), &game->ceiling_color));
	return (-1);
}

int	process_config_line(t_game *game, char *trimmed, int *parsed)
{
	int	res;

	res = handle_texture_line(game, trimmed);
	if (res == 0)
		return (0);
	if (res == 1)
	{
		*parsed += 1;
		return (1);
	}
	res = handle_color_line(game, trimmed);
	if (res == 0)
		return (0);
	if (res == 1)
	{
		*parsed += 1;
		return (1);
	}
	printf("Error\nInvalid configuration!\n");
	return (0);
}

int	handle_config_line(t_game *game, char *trimmed, int *parsed)
{
	if (*trimmed == '\0')
		return (1);
	if (!process_config_line(game, trimmed, parsed))
		return (0);
	return (1);
}
