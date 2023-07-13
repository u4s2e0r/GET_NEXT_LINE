/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:12:16 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/12 07:48:17 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*gnltest(int fd, size_t BUFFER_SIZE)
{
	static char *reserve;
	char *next_line;
	char *buffer;
	ssize_t	read_return;
	
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	buffer[BUFFER_SIZE + 1] = '\0';
	if (!buffer)
		return (NULL);
	read_return = read(fd, buffer, BUFFER_SIZE);
	if (read_return == 0 || read_return < 0)
		return (NULL);
	if (reserve)
		reserve = ft_strjoin(reserve, buffer);
	else
		reserve = ft_strdup(buffer);
	while (ft_strchr(reserve, '\n'))
	{
		next_line = ft_substr(reserve, 0, (size_to_nl(reserve) + 1));
		reserve = ft_strdup((ft_strchr(reserve, '\n') + 1));
	}
	if (reserve == NULL)
	{
		next_line = NULL;
	}
	return (next_line);
