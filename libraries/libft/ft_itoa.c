/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:52:48 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/21 18:28:13 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	int		len;
	char	*resualt;

	if (nbr == -2147483648)
		return ("-2147483648");
	len = int_len(nbr);
	resualt = ft_malloc(sizeof(char) * (len + 1));
	resualt[len] = '\0';
	if (nbr == 0)
	{
		resualt[0] = '0';
		return (resualt);
	}
	if (nbr < 0)
	{
		resualt[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		resualt[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (resualt);
}
