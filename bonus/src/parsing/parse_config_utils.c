/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:40:00 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/11 19:06:12 by moirhira         ###   ########.fr       */
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
		*parsed += parse_texture(get_arg(trimmed), &game->tex_paths[0]);
	else if (ft_strncmp("SO ", trimmed, 3) == 0)
		*parsed += parse_texture(get_arg(trimmed), &game->tex_paths[1]);
	else if (ft_strncmp("WE ", trimmed, 3) == 0)
		*parsed += parse_texture(get_arg(trimmed), &game->tex_paths[2]);
	else if (ft_strncmp("EA ", trimmed, 3) == 0)
		*parsed += parse_texture(get_arg(trimmed), &game->tex_paths[3]);
	else if (ft_strncmp("DO ", trimmed, 3) == 0)
		*parsed += parse_texture(get_arg(trimmed), &game->tex_paths[4]);
	else if (ft_strncmp("F ", trimmed, 2) == 0)
		*parsed += parse_color(get_arg(trimmed), &game->floor_color);
	else if (ft_strncmp("C ", trimmed, 2) == 0)
		*parsed += parse_color(get_arg(trimmed), &game->ceiling_color);
	else
		return (0);
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
