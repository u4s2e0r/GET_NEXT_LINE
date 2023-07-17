/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:12:16 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/17 18:14:36 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*rc_sameas_bs(char *reserve, char *buffer, size_t read_return, size_t read_count, int fd)
{
	char	*result;

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
	result = ft_substr(reserve, 0, (size_to_nl(reserve) + 1));
	reserve = ft_strdup((ft_strchr(reserve, '\n') + 1));
	return (result);
}

static char	*rc_unlike_bs(char *reserve, char *buffer, size_t read_return)
{
	char	*result;

	if (reserve && *buffer)
		reserve = ft_strjoin(reserve, buffer);
	else if (!reserve)
		reserve = ft_strdup(buffer);
	if (!ft_strchr(reserve, '\n') && read_return == 0)
	{
		result = ft_strdup(reserve);
		reserve = NULL;
	}
	else
	{
		result = ft_substr(reserve, 0, (size_to_nl(reserve) + 1));
		reserve = ft_strdup((ft_strchr(reserve, '\n') + 1));
	}
	return (result);
}

static char	*read_and_fill(char *buffer, char *next_line, size_t read_count, int fd)
{
	static char	*reserve;
	ssize_t	read_return;

	read_return = read(fd, buffer, BUFFER_SIZE);
	read_count++;
	buffer[read_return] = '\0';
	if ((read_return < 0) || (read_return == 0 && !reserve))
		return (NULL);
	if (read_return == (ssize_t)BUFFER_SIZE)
		next_line = rc_sameas_bs(reserve, buffer, read_return, read_count, fd);
	else if (read_count == 1 && read_return != (ssize_t)BUFFER_SIZE)
		next_line = rc_unlike_bs(reserve, buffer, read_return);
	return (next_line);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*next_line;
	size_t read_count;

	read_count = 0;
	next_line = NULL;
	if(BUFFER_SIZE == 0|| fd < 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	next_line = read_and_fill(buffer, next_line, read_count, fd);
	return (next_line);
}

int	main(void)
{
	char *result;
	int	fd = open("test.txt", O_RDONLY);
	printf("fd = %d\nBUFFER_SIZE = %d\n", fd, BUFFER_SIZE);
	while(result != NULL)
	{
		result = get_next_line(fd);
		printf("GNL : %s\n", result);
	}
	close(fd);
}