/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprudenc <nprudenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:30:45 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/15 19:03:38 by nprudenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*load_buffer(int fd, char *line_storage, char *buffer)
{
	int		bytes_read;
	char	*aux;

	bytes_read = 1;
	while (bytes_read > 0)
	{	
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (!line_storage)
			line_storage = ft_strdup("");
		buffer[bytes_read] = '\0';
		aux = line_storage;
		line_storage = ft_strjoin(aux, buffer);
		free(aux);
		if (ft_strchr(line_storage, '\n'))
			break ;
	}
	return (line_storage);
}

char	*clean_buffer(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		str[j++] = line[i++];
	str[j] = line[i];
	free(line);
	return (str);
}

char	*rest_cpy(char	*line)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (ft_strchr(line, '\n'))
		line = ft_strchr(line, '\n') + 1;
	else
		return (NULL);
	while (line[k])
		k++;
	str = ft_calloc(k + 1, sizeof(char));
	while (line[i])
		str[j++] = line[i++];
	return (str);
}

char	*get_next_line(int fd)
{	
	static char	*line_storage;
	char		*buffer;
	char		*line;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	line = load_buffer(fd, line_storage, buffer);
	free(buffer);
	line_storage = rest_cpy(line);
	line = clean_buffer(line);
	if (*line == '\0')
	{	
		free(line);
		return (NULL);
	}
	return (line);
}
