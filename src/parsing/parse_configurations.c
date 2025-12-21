/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configurations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:40:00 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/21 12:22:46 by moirhira         ###   ########.fr       */
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

int	process_config_line(t_game *game, char *trimmed, int *parsed)
{
	if (ft_strncmp("NO ", trimmed, 3) == 0)
	{
		if (parse_texture(get_arg(trimmed), &game->tex_paths[0]) == 0)
			return (0);
		*parsed += 1;
	}
	else if (ft_strncmp("SO ", trimmed, 3) == 0)
	{
		if (parse_texture(get_arg(trimmed), &game->tex_paths[1]) == 0)
			return (0);
		*parsed += 1;
	}
	else if (ft_strncmp("WE ", trimmed, 3) == 0)
	{
		if (parse_texture(get_arg(trimmed), &game->tex_paths[2]) == 0)
			return (0);
		*parsed += 1;
	}
	else if (ft_strncmp("EA ", trimmed, 3) == 0)
	{
		if (parse_texture(get_arg(trimmed), &game->tex_paths[3]) == 0)
			return (0);
		*parsed += 1;
	}
	else if (ft_strncmp("F ", trimmed, 2) == 0)
	{
		if (parse_color(get_arg(trimmed), &game->floor_color) == 0)
			return (0);
		*parsed += 1;
	}
	else if (ft_strncmp("C ", trimmed, 2) == 0)
	{
		if (parse_color(get_arg(trimmed), &game->ceiling_color) == 0)
			return (0);
		*parsed += 1;
	}
	else
		return (0);
	return (1);
}

int	handle_config_line(t_game *game, char *line, char *trimmed, int *parsed)
{
	if (*trimmed == '\0')
	{
		free(trimmed);
		free(line);
		return (1);
	}
	if (!process_config_line(game, trimmed, parsed))
	{
		free(trimmed);
		free(line);
		return (0);
	}
	free(trimmed);
	free(line);
	return (1);
}

void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
}
