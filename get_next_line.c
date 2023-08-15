/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:19:46 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/30 19:25:55 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	read_and_fill(char *buffer, int fd, char **reserve)
{
	ssize_t	read_ret;
	char	*tmp;

	read_ret = 42;
	if (!*reserve)
		*reserve = ft_strdup("");
	while (!ft_strchr(*reserve, '\n') && read_ret != 0)
	{
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if ((read_ret < 0) || (read_ret == 0 && !**reserve))
			return (-1);
		buffer[read_ret] = '\0';
		tmp = *reserve;
		*reserve = ft_strjoin(*reserve, buffer);
		free(tmp);
		tmp = NULL;
	}
	if (!ft_strchr(*reserve, '\n') && read_ret == 0)
		return (-42);
	else
		return (read_ret);
}

static char	*build_next_line(char **reserve)
{
	char	*tmp;
	char	*line;

	line = ft_substr(*reserve, 0, (ft_strlen(*reserve, 2) + 1));
	tmp = *reserve;
	*reserve = ft_strdup((ft_strchr(*reserve, '\n') + 1));
	free(tmp);
	tmp = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*next_line;
	static char	*reserve;
	int			check_behavior;

	check_behavior = 0;
	if (BUFFER_SIZE == 0 || fd < 0)
		return (NULL);
	buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	check_behavior = read_and_fill(buffer, fd, &reserve);
	free(buffer);
	buffer = NULL;
	if (check_behavior == -1)
		return (NULL);
	if (check_behavior == -42)
	{
		next_line = ft_strdup(reserve);
		free(reserve);
		reserve = NULL;
	}
	else
		next_line = build_next_line(&reserve);
	return (next_line);
}

// int	main(void)
// {
// 	char *result;
// 	int	fd = open("test.txt", O_RDONLY);
// 	printf("fd = %d\nBUFFER_SIZE = %d\n", fd, BUFFER_SIZE);
// 	result = get_next_line(fd);
// 	printf("GNL : %s\n", result);
// 	while(result != NULL)
// 	{
// 		result = get_next_line(fd);
// 		printf("GNL : %s\n", result);
// 	}
// 	close(fd);
// }
