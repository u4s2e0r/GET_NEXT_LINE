/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/07/25 19:19:46 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/25 21:53:32 by pmateo           ###   ########.fr       */
=======
/*   Created: 2023/07/04 17:12:16 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/19 19:10:39 by pmateo           ###   ########.fr       */
>>>>>>> e168632fe6e51a46f9ddfd2f7825455f8ba97099
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// vérifier le cas ou il n'il y a pas de backslash n
static int read_and_fill(char *buffer, int fd,char **reserve)
{
<<<<<<< HEAD
	ssize_t read_ret;
	char	*tmp;
	
	read_ret = 42;
	if (!*reserve)
		*reserve = ft_strdup("");
	while (!ft_strchr(*reserve, '\n') && read_ret != 0)
	{
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if((read_ret < 0) || (read_ret == 0 && !**reserve))//!**reserve ?
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
=======
	if (reserve && *buffer)
		reserve = ft_strjoin(reserve, buffer);
	else if (!reserve)
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
		free(reserve);
		reserve = NULL;
	}
	else
	{
		*next_line = ft_substr(reserve, 0, (size_to_nl(reserve) + 1));
		reserve = ft_strdup((ft_strchr(reserve, '\n') + 1));
		if (!*reserve)
		{
			free(reserve);
			reserve = NULL;
		}
	}
	return (reserve);
>>>>>>> e168632fe6e51a46f9ddfd2f7825455f8ba97099
}

static char	*build_next_line(char **reserve)
{
<<<<<<< HEAD
	char	*tmp;
	char	*line;

	line = ft_substr(*reserve, 0, (size_to_nl(*reserve) + 1));
	tmp = *reserve;
	*reserve = ft_strdup((ft_strchr(*reserve, '\n') + 1));
	free(tmp);
	tmp = NULL;
	return (line);
=======
	if (reserve && *buffer)
		reserve = ft_strjoin(reserve, buffer);
	else if (!reserve)
		reserve = ft_strdup(buffer);
	if (!ft_strchr(reserve, '\n') && *reserve)
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
	if ((read_return < 0) || (read_return == 0 && !reserve))
		return (NULL);
	buffer[read_return] = '\0';
	if (read_return == (ssize_t)BUFFER_SIZE)
		reserve = rc_sameas_bs(reserve, buffer, next_line, read_return, fd);
	else if (read_return != (ssize_t)BUFFER_SIZE)
		reserve = rc_unlike_bs(reserve, buffer, next_line);
	return (reserve);
>>>>>>> e168632fe6e51a46f9ddfd2f7825455f8ba97099
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*next_line;
	static char	*reserve;
	int	check_behavior;
	
	check_behavior = 0;
	if (BUFFER_SIZE == 0 || fd < 0)
		return (NULL);
	buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	check_behavior = read_and_fill(buffer, fd, &reserve);
	free(buffer);
	buffer = NULL;
<<<<<<< HEAD
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

int	main(void)
{
	char *result;
	int	fd = open("test.txt", O_RDONLY);
	printf("fd = %d\nBUFFER_SIZE = %d\n", fd, BUFFER_SIZE);
	result = get_next_line(fd);
	printf("GNL : %s\n", result);
	while(result != NULL)
	{
		result = get_next_line(fd);
		printf("GNL : %s\n", result);
	}
	close(fd);
}
=======
	return (next_line);
}

// int	main(void)
// {
// 	char *result;
// 	int	fd = open("41_no_nl.txt", O_RDONLY);
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
>>>>>>> e168632fe6e51a46f9ddfd2f7825455f8ba97099
