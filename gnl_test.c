/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:12:21 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/12 08:43:05 by pmateo           ###   ########.fr       */
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


// void	read_and_check(char *buffer, int fd, size_t BUFFER_SIZE)
// {
// 	ssize_t read_return;

// 	read_return = read(fd, buffer, BUFFER_SIZE);
// 	if()
// }

char	*gnltest(int fd, size_t BUFFER_SIZE)
{
	static char *reserve;
	char *next_line;
	char *buffer;
	ssize_t	read_return;
	
	if(BUFFER_SIZE == 0)
		return(NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE + 1] = '\0';
	read_return = read(fd, buffer, BUFFER_SIZE);
	if (read_return < 0)
		return (NULL);
	while (read_return != 0)
	{
		if (reserve)
			reserve = ft_strjoin(reserve, buffer);
		else
			reserve = ft_strdup(buffer);
		while (ft_strchr(reserve, '\n'))
		{
			next_line = ft_substr(reserve, 0, (size_to_nl(reserve) + 1));
			reserve = ft_strdup((ft_strchr(reserve, '\n') + 1));
			break;
		}
	}
	if (!read_return)
	{
		while (reserve)
		{
			reserve = ft_strjoin(reserve, buffer);
		}
		
	}
	if (reserve == NULL)
	{
		next_line = NULL;
	}
	return (next_line);
}

int	main(void)
{
	// "Il etait une fois l'histoire d'un ado"; len = 37 (Il etait une fois = 17)
	size_t BUFFER_SIZE = 100;
	char *result;
	int	fd = open("test.txt", O_RDONLY);
	printf("fd = %d\nBUFFER_SIZE = %ld\n", fd, BUFFER_SIZE);
	// printf("retour de read : %ld\n", read(fd, buffer, BUFFER_SIZE));
	// gnltest(fd, BUFFER_SIZE, buffer);
	while(result != NULL)
	{
		result = gnltest(fd, BUFFER_SIZE);
		printf("GNL : %s\n", result);
	}
}

// int	main(void)
// {
// 	size_t BUFFER_SIZE = 10000;
// 	char	*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	int fd = open("test.txt", O_RDONLY);
// 	read(fd, buffer, BUFFER_SIZE);
// 	buffer[BUFFER_SIZE + 1] = '\0';
// 	printf(" ")
// }