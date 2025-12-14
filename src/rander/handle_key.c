/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:03:50 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/14 02:21:59 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press_handler(int keycode, t_game *game)
{
	printf("Key pressed! Keycode: %d\n", keycode);
	if (keycode == ESC_KEY)
	{
		close_and_free(game);
		exit(0);
	}
	else if (keycode == 'w' || keycode == KEY_UP)
		game->keys.w = 1;
	else if (keycode == 's' || keycode == KEY_DOWN)
		game->keys.s = 1;
	else if (keycode == 'a')
		game->keys.a = 1;
	else if (keycode == 'd')
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left_arrow = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right_arrow = 1;
	return (0);
}

int	key_release_handler(int keycode, t_game *game)
{
	printf("Key released! Keycode: %d\n", keycode);
	if (keycode == 'w' || keycode == KEY_UP)
		game->keys.w = 0;
	else if (keycode == 's' || keycode == KEY_DOWN)
		game->keys.s = 0;
	else if (keycode == 'a')
		game->keys.a = 0;
	else if (keycode == 'd')
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left_arrow = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right_arrow = 0;
	return (0);
}
