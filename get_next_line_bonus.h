/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:19:10 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/30 19:27:07 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

size_t		ft_strlen(const char *str, int c);
char		*ft_strchr(const char *str, int c);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_substr(const char *src, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, char const *s2);
char		*get_next_line(int fd);

#endif