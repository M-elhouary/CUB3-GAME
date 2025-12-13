/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:58:15 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/11 20:53:40 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		calclen(char *str);
char	*find_newline(char *data, int ch);
char	*separate_line(char *data);
char	*update_buffer(char *data);
char	*my_strdup(char *src);
void	ft_copy(char *dest, const char *src);
void	ft_strcat(char *dest, const char *src);
char	*get_line(int fd);

#endif
