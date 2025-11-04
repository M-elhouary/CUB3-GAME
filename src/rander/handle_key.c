/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:03:50 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/04 23:10:03 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int handle_key(int key, void *param)
{
    (void)param;
    if (key == ESC_KEY)
        exit(0);
    return (0);
}

int handle_win_close(void *param)
{
    (void)param;
    //free
    exit(0);
}