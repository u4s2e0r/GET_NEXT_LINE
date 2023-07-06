/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:12:21 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/06 20:19:41 by pmateo           ###   ########.fr       */
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


// le but de cette fonction sera dans un premier temps d'effectuer des tests de manipulations pour 
// qu'après un appel de la fonction gnltest() *str soit récupérer depuis le fichier test par open et
// read et stockée entièrement malgré un buffer_size de 17 qui est donc sensé la lire en 3 fois.

char	*gnltest(int fd, size_t BUFFER_SIZE, char *buffer)
{
	static char	*reserve;
	char	*tmp;
	int	newlinefound;
	int	sizeofnl;
	char	*tmpsave;
	int	countcpy;
	
	sizeofnl = 0;
	newlinefound = 0;
	tmp[0] = '\0';
	while(newlinefound != 1)
	{
		read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
		ft_strlcpy(tmp, buffer, BUFFER_SIZE + 1);
		countcpy++;
		if(countcpy == 1)
			tmpsave = tmp;
		if(ft_strchr(buffer, '\n'))
		{
			tmp = ft_substr(tmpsave, 0, (ft_strchr(tmp, '\n') - tmpsave));
			sizeofnl = ft_strlen(tmp);
			newlinefound = 1;
			reserve = malloc(sizeofnl * sizeof(char));
			ft_strlcpy(reserve, tmp, sizeofnl);
			return (reserve);
		}
		tmp += BUFFER_SIZE;
	}
	return (reserve);
}

int	main(void)
{
	// "Il etait une fois l'histoire d'un ado"; len = 37 (Il etait une fois = 17)
	size_t BUFFER_SIZE = 17;
	int	fd = open("test.txt", O_RDONLY);
	printf("fd = %d\nBUFFER_SIZE = %ld\n", fd, BUFFER_SIZE);
	char *buffer;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		exit(EXIT_FAILURE);
	// printf("retour de read : %ld\n", read(fd, buffer, BUFFER_SIZE));
	// gnltest(fd, BUFFER_SIZE, buffer);
	char *result = gnltest(fd, BUFFER_SIZE, buffer);
	printf("GNL : %s\n", result);
	printf("mon buffer contient : '%s'\n", buffer);
	free(buffer);
}