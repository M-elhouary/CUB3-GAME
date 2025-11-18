/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:44:44 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/30 10:56:08 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	**ft_split(char const *s, char c);
char	**free_split(char **res);
int		ft_strlen_2d(char **str);
int		ft_strlen(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_itoa(int nbr);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strrchr(char *str, int ch);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char *s1, char *set);
int	ft_atoi(const char *str);
char	*ft_strdup( char *str);
void	*ft_memcpy(void *d_str, const void *s_str, size_t n);
void	*ft_memset(void *s, int c, size_t n);
#endif
