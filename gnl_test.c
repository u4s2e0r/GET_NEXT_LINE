/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:12:21 by pmateo            #+#    #+#             */
/*   Updated: 2023/07/04 20:54:24 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// Fonctions utiles : -strrchr ou strchr;
// 				   -strlen;
// 				   -strdup;
// 				   -strjoin;

// le but de cette fonction sera dans un premier temps d'effectuer des tests de manipulations pour 
// qu'après un appel de la fonction gnltest() *str soit récupérer depuis le fichier test par open et
// read et stockée entièrement malgré un buffer_size de 17 qui est donc sensé la lire en 3 fois.

// char	*gnltest(int fd, size_t BUFFER_SIZE)
// {
// 	char	*buffer;
// 	char	*reserve;
// }

int	main(void)
{
	// char *str = "Il etait une fois l'histoire d'un ado"; // len = 37 (Il etait une fois = 17)
	size_t BUFFER_SIZE = 17;
	int	fd = open("test.txt", O_RDONLY);
	printf("fd = %d\nBUFFER_SIZE = %ld\n", fd, BUFFER_SIZE);
	char *buffer;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		exit(EXIT_FAILURE);
	printf("retour de read : %ld\n", read(fd, buffer, BUFFER_SIZE));
	printf("mon buffer contient : '%s'\n", buffer);
	// char *result = gnltest(fd);
	// printf("%s\n", result);
}