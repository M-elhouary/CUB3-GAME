/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:53:36 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/21 21:54:35 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_file_extension(char *file)
{
	char	*ext;

	ext = ft_strrchr(file, '.');
	if (!ext || ft_strcmp(ext, ".cub") != 0)
	{
		printf("Error\nBad extension!\n");
		return (0);
	}
	return (1);
}

int	parse(t_map *map, char *filedata)
{
    int	i;
	int	fd;
    
    if (!validate_file_extension(filedata))
		return (0);
	fd = open(filedata, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nopening file\n"), 0);
        

    // read and parse map.config here
    close (fd);
    return (1);
}