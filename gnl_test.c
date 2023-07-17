/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:12:21 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/17 15:29:51 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	size_to_nl(const char *str)
{
	size_t i;

	i = 0;
	while(str[i] != '\n')
		i++;
	return (i);
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(const char *src, unsigned int start, size_t len)
{
	char	*str;
	size_t	strlen;
	
	if (!src)
		return(NULL);
	if (start > ft_strlen(src))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	else
	{
		strlen = len;
		if (ft_strlen(src + start) < len)
			strlen = ft_strlen(src + start);
		str = malloc((strlen + 1) * sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, src + start, strlen + 1);
		return (str);
	}
}

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	size = ft_strlen(s1) + 1;
	s2 = malloc(size * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	size_t			size;
	char			*str;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(size * sizeof(char));
	if (str == NULL)
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

char	*gnltest(int fd, size_t BUFFER_SIZE)
{
	static char *reserve;
	char *next_line;
	char *buffer;
	ssize_t	read_return;
	size_t	read_count;
	
	read_count = 0;
	if(BUFFER_SIZE == 0)
		return(NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_return = read(fd, buffer, BUFFER_SIZE);
	read_count++;
	buffer[read_return] = '\0';
	if (read_return < 0)
		return (NULL);
	if (read_return == 0 && !reserve)
		return (NULL);
	if (read_return == (ssize_t)BUFFER_SIZE)
	{
		if (reserve)
				reserve = ft_strjoin(reserve, buffer);
			else
				reserve = ft_strdup(buffer);
		
		while (!ft_strchr(reserve, '\n') || read_return	!= 0)
		{
			read_return = read(fd, buffer, BUFFER_SIZE);
			buffer[read_return] = '\0';
			reserve = ft_strjoin(reserve, buffer);
			read_count++;
		}
		next_line = ft_substr(reserve, 0, (size_to_nl(reserve) + 1));
		reserve = ft_strdup((ft_strchr(reserve, '\n') + 1));
	}
	if(read_count == 1 && read_return != (ssize_t)BUFFER_SIZE)
	{
		if (reserve && *buffer)
			reserve = ft_strjoin(reserve, buffer);
		else if (!reserve)
			reserve = ft_strdup(buffer);
		if (!ft_strchr(reserve, '\n') && read_return == 0)
		{
			next_line = ft_strdup(reserve);
			reserve = NULL;
		}
		else
		{
			next_line = ft_substr(reserve, 0, (size_to_nl(reserve) + 1));
			reserve = ft_strdup((ft_strchr(reserve, '\n') + 1));
		}
	}
	return (next_line);
}

int	main(void)
{
	size_t BUFFER_SIZE = 2;
	char *result;
	int	fd = open("test.txt", O_RDONLY);
	printf("fd = %d\nBUFFER_SIZE = %ld\n", fd, BUFFER_SIZE);
	while(result != NULL)
	{
		result = gnltest(fd, BUFFER_SIZE);
		printf("GNL : %s\n", result);
	}
}
