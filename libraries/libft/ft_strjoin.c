/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:12:32 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/11 16:32:32 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcoopy(char *dest, const char *src, size_t start)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[start + i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!ptr)
		return (NULL);
	ft_strcoopy(ptr, s1, 0);
	ft_strcoopy(ptr, s2, s1len);
	ptr[s1len + s2len] = '\0';
	return (ptr);
}
