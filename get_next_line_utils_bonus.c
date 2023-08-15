/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:48:52 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/30 19:24:40 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str, int c)
{
	size_t	i;

	i = 0;
	if (c == 1)
	{
		while (str[i] != '\0')
			i++;
		return (i);
	}
	else
	{
		while (str[i] != '\n')
			i++;
		return (i);
	}
}

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		else
			i++;
	}
	if (str[i] == c)
		return ((char *)str + i);
	return (NULL);
}

char	*ft_substr(const char *src, unsigned int start, size_t len)
{
	char	*str;
	size_t	strlen;

	if (!src)
		return (NULL);
	if (start > ft_strlen(src, 1))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	else
	{
		strlen = len;
		if (ft_strlen(src + start, 1) < len)
			strlen = ft_strlen(src + start, 1);
		str = malloc((strlen + 1) * sizeof(char));
		if (!str)
			return (NULL);
		str[strlen] = '\0';
		while (strlen-- > 0)
			str[strlen] = src[start + strlen];
	}
	return (str);
}

char	*ft_strdup(const char *src)
{
	char		*s;
	int			i;

	i = 0;
	s = malloc((ft_strlen(src, 1) + 1) * sizeof(*src));
	if (!s)
		return (NULL);
	while (src[i])
	{
		s[i] = src[i];
		i++;
	}
	s[i] = 0;
	return (s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	size_t			size;
	char			*str;

	i = 0;
	j = 0;
	size = ft_strlen(s1, 1) + ft_strlen(s2, 1) + 1;
	str = malloc(size * sizeof(char));
	if (!str || !s1 || !s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
