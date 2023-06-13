/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprudenc <nprudenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:30:45 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/12 22:28:46 by nprudenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(const char	*s)
{	
	int	i;

	i = 0;
	while (*s)
	{	
		i++;
		s++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2) + 1;
	str = (char *)malloc((s1_len + s2_len) * sizeof(char));
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{	
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		counter;
	int		i;
	char	*str;

	counter = ft_strlen(s) + 1;
	str = (char *)malloc(counter * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{	
	char			*str;
	size_t			s_size;
	size_t			i;

	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (start > s_size)
		return (ft_strdup(""));
	if (len > s_size - start)
		len = s_size - start;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*copy_line(int fd, char	*line_storage, char *buffer)
{
	int		bytes_read;
	char	*free_line;

	bytes_read = 1;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		else if (bytes_read == 0)
			break ;	
		buffer[bytes_read] = '\0';
		if (!line_storage)
			line_storage = ft_strdup("");
		free_line = line_storage;
		line_storage = ft_strjoin(free_line, buffer);
		free(free_line);
		if (ft_strchr(line_storage, '\n'))
			break ;
	}
	return (line_storage);
}

char	*clean_line(char *line, char *line_storage)
{	
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	line_storage = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*line_storage == '\0')
	{
		free(line_storage);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (line_storage);
}

char	*get_next_line(int fd)
{	
	char		*buffer;
	char		*line;
	static char	*line_storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = copy_line(fd, line_storage, buffer);
	free(buffer);
	if (!line)
		return (line);
	line_storage = clean_line(line, line_storage);
	return (line);
}

/*
	3 variáveis, buffer (armazenar resultado de read), nextline_save(static -> armazenar inicio da segunda linha)
	line -> linha atual

	1 - mallocar espaço no buffer, e chamar a função que executa a leitura da linha
	2 - na função copy_line, usar read() para trazer os dados lidos ao buffer
	3 - copiar os dados do buffer para a string e também trazer o início do nextline caso ele exista
	4 - separar o final da linha com o início da próxima
*/

// int	main(void)
// {
// 	FILE	*arquivo;
// 	char	*linha;

// 	arquivo = fopen("teste.txt", "r");
// 	if (!arquivo)
// 	{
// 		printf("Erro ao abrir o arquivo.\n");
// 		return (1);
// 	}
// 	linha = get_next_line(fileno(arquivo));
// 	printf("%s", linha);
// 	linha = get_next_line(fileno(arquivo));
// 	printf("%s", linha);
// 	linha = get_next_line(fileno(arquivo));
// 	printf("%s", linha);
// 	fclose(arquivo);
// 	return (0);
// }
