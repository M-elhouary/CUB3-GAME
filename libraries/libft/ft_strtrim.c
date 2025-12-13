/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:12:47 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/22 12:16:39 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkset(char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*trimedstr;
	size_t	ibg;
	size_t	iend;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	iend = ft_strlen(s1);
	ibg = 0;
	while (s1[ibg] && ft_checkset(set, s1[ibg]))
		ibg++;
	while (iend > ibg && ft_checkset(set, s1[iend - 1]))
		iend--;
	trimedstr = (char *)malloc(sizeof(char) * (iend - ibg + 1));
	if (!trimedstr)
		return (NULL);
	i = 0;
	while (iend > ibg)
	{
		trimedstr[i++] = s1[ibg++];
	}
	trimedstr[i] = '\0';
	return (trimedstr);
}