/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:44:44 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/11 16:33:24 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	**ft_split(char const *s, char c);
char	**free_split(char **res, size_t indx);
int		ft_strlen_2d(char **str);
int		ft_strlen(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_itoa(int nbr);
char	*ft_strjoin(char *s1, char *s2);

#endif
