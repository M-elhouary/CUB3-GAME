/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:32:37 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/23 09:33:04 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_dir(char *arg)
{
	int		fd;

	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		return (1);
	}
	return (0);
}

int is_all_digits(char *str)
{
    if (!str || *str == '\0')
        return (0);
    while (*str == ' ' || *str == '\t')
        str++;
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return (0);
        str++;
    }
    return (1);
}

int ft_isempty(char *str)
{
    int i;

    if (!str)
        return (1);
    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}