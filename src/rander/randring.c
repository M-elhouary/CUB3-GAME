/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:23:49 by mel-houa          #+#    #+#             */
/*   Updated: 2025/09/23 15:38:22 by mel-houa         ###   ########.fr       */
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
    exit(0);
}