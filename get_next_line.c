/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:12:16 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/18 22:00:43 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*rc_sameas_bs(char *reserve, char *buffer, char **next_line, size_t read_return, int fd)
{
	if (reserve)
		reserve = ft_strjoin(reserve, buffer);
	else
		reserve = ft_strdup(buffer);
	while (!ft_strchr(reserve, '\n') && read_return	!= 0)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		buffer[read_return] = '\0';
		reserve = ft_strjoin(reserve, buffer);
	}
	if (read_return == 0)
	{
		*next_line = ft_strdup(reserve);
		reserve = NULL;
	}
	else
	{
		*next_line = ft_substr(reserve, 0, (size_to_nl(reserve) + 1));
		reserve = ft_strdup((ft_strchr(reserve, '\n') + 1));
	}
	return (reserve);
}

static char	*rc_unlike_bs(char *reserve, char *buffer, char **next_line)
{
	if (reserve && *buffer)
		reserve = ft_strjoin(reserve, buffer);
	else if (!reserve)
		reserve = ft_strdup(buffer);
	if (!ft_strchr(reserve, '\n'))
	{
		*next_line = ft_strdup(reserve);
		free(reserve);
		reserve = NULL;
	}
	else
	{
		*next_line = ft_substr(reserve, 0, (size_to_nl(reserve) + 1));
		reserve = ft_strdup((ft_strchr(reserve, '\n') + 1));
	}
	return (reserve);
}

static char	*read_and_fill(char *buffer, char *reserve, char **next_line, int fd)
{
	ssize_t	read_return;

	read_return = read(fd, buffer, BUFFER_SIZE);
	buffer[read_return] = '\0';
	if ((read_return < 0) || (read_return == 0 && !reserve))
		return (NULL);
	if (read_return == (ssize_t)BUFFER_SIZE)
		reserve = rc_sameas_bs(reserve, buffer, next_line, read_return, fd);
	else if (read_return != (ssize_t)BUFFER_SIZE)
		reserve = rc_unlike_bs(reserve, buffer, next_line);
	return (reserve);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*next_line;
	static char	*reserve;

	next_line = NULL;
	if(BUFFER_SIZE == 0|| fd < 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	reserve = read_and_fill(buffer, reserve, &next_line, fd);
	free(buffer);
	return (next_line);
}

int	main(void)
{
	char *result;
	int	fd = open("alternate_line_nl_with_nl.txt", O_RDONLY);
	printf("fd = %d\nBUFFER_SIZE = %d\n", fd, BUFFER_SIZE);
	while(result != NULL)
	{
		result = get_next_line(fd);
		printf("GNL : %s\n", result);
	}
	close(fd);
}