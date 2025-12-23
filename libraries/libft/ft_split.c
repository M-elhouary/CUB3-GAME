/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:55:19 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/21 19:37:37 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ctrword(char const *s, char c)
{
	size_t	wordctr;
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	wordctr = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || c == s[i - 1]))
			wordctr++;
		i++;
	}
	return (wordctr);
}

static char	*ft_memalloc(char const *s, size_t len)
{
	size_t	i;
	char	*ptr;

	ptr = ft_malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

static char	*copy_word(const char **s, char c)
{
	const char	*start;
	size_t		len;

	start = *s;
	len = 0;
	while (**s && **s != c)
	{
		len++;
		(*s)++;
	}
	return (ft_memalloc(start, len));
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;

	i = 0;
	res = ft_malloc(sizeof(char *) * (ft_ctrword(s, c) + 1));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res[i] = copy_word(&s, c);
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
