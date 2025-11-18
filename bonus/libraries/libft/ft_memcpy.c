/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:54:38 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/30 10:54:41 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d_str, const void *s_str, size_t n)
{
	unsigned char		*dest_str;
	const unsigned char	*src_str;
	size_t				i;

	dest_str = (unsigned char *)d_str;
	src_str = (const unsigned char *)s_str;
	i = 0;
	if (n == 0 || d_str == s_str)
	{
		return (d_str);
	}
	while (i < n)
	{
		dest_str[i] = src_str[i];
		i++;
	}
	return (d_str);
}