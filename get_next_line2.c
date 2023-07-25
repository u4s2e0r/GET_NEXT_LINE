/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:12:16 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/25 18:53:24 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// variable temporaire, tmp = reserve; reserve=ft(); free(tmp);
// couper rc sameas bs en deux

static int rc_sameas_bs(char **reserve, char *buffer, char **next_line, int fd)
{
	ssize_t	read_return;
	char	*tmp;
	
	while (!ft_strchr(*reserve, '\n') && read_return != 0)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		buffer[read_return] = '\0';
		tmp = *reserve;
		*reserve = ft_strjoin(*reserve, buffer);
		free(tmp);
		tmp = NULL;
	}
	if (read_return == 0)
	{
		*next_line = ft_strdup(*reserve);
		free(*reserve);
		*reserve = NULL;
		return (0);
	}
	else
		return (1);
}

static int rc_unlike_bs(char **reserve, char *buffer, char **next_line)
{
	char	*tmp;
	
		if (*reserve && *buffer)
		{
			tmp = *reserve;
			*reserve = ft_strjoin(*reserve, buffer);
			free(tmp);
			tmp = NULL;
		}
		else if (!reserve)
			*reserve = ft_strdup(buffer);
		if (!ft_strchr(*reserve, '\n'))
		{
			*next_line = ft_strdup(*reserve);
			free(*reserve);
			*reserve = NULL;
			return (0);
		}
	return (1);
}

static int fill(char *buffer, char **reserve, char **next_line, int fd)
{
	ssize_t	read_return;
	int	ret;
	
	ret = 42;
	read_return = read(fd, buffer, BUFFER_SIZE);
	if ((read_return < 0) || (read_return == 0 && !*reserve))
		return (0);
	buffer[read_return] = '\0';
	if (*reserve && *buffer)
		*reserve = ft_strjoin(*reserve, buffer);
	else if (!*reserve)
		*reserve = ft_strdup(buffer);
	if (read_return == (ssize_t)BUFFER_SIZE)
		ret = rc_sameas_bs(reserve, buffer, next_line, fd);
	else if (read_return != (ssize_t)BUFFER_SIZE)
		ret = rc_unlike_bs(reserve, buffer, next_line);
	if (ret == 1)
	{
		*next_line = ft_substr(*reserve, 0, (size_to_nl(*reserve) + 1));
		*reserve = ft_strdup((ft_strchr(*reserve, '\n') + 1));
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*next_line;
	static char	*reserve;
	int	fill_ret;

	next_line = NULL;
	if(BUFFER_SIZE == 0|| fd < 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	fill_ret = fill(buffer, &reserve, &next_line, fd);
	if (fill_ret == 0)
		return (NULL);
	free(buffer);
	return (next_line);
}

int	main(void)
{
	char *result;
	int	fd = open("test.txt", O_RDONLY);
	printf("fd = %d\nBUFFER_SIZE = %d\n", fd, BUFFER_SIZE);
	result = get_next_line(fd);
	while(result != NULL)
	{
		result = get_next_line(fd);
		printf("GNL : %s\n", result);
	}
	close(fd);
}