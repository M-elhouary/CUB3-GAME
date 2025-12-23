/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:32:37 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/21 19:48:31 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	is_dir(char *arg)
{
	int	fd;

	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}

int	is_all_digits(char *str)
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

int	ft_isempty(char *str)
{
	int	i;

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

void	free_close_helper(t_game *game)
{
	if (game->img)
	{
		if (game->img->img_ptr && game->mlx)
			mlx_destroy_image(game->mlx, game->img->img_ptr);
		game->img = NULL;
	}
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

int	close_and_free(t_game *game)
{
	int	i;

	if (!game)
		exit(0);
	i = 0;
	while (i < 5)
	{
		if (game->textures[i].img_ptr && game->mlx)
			mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
		i++;
	}
	free_close_helper(game);
	free_all_memory();
	exit(0);
}
