/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:25:20 by nprudenc          #+#    #+#             */
/*   Updated: 2023/06/10 10:39:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	line_cnt(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*my_strchr(const char *s, int c)
{
	while (*s)
	{	
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (!(unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*str_concat(char *str, char *buff)
{	
	static char	*next_line;
	int			i;
	int			j;

	str = malloc(line_cnt(buff) + 1 * sizeof(char));
	next_line = malloc(line_cnt(buff) + 1 * sizeof(char));
	if (!str || !next_line)
		return (NULL);
	i = 0;
	j = 0;
	while (buff[i] != '\n') // anda até o término da primeira linha
		i++;
	while (buff[++i])
		next_line[j++] = buff[i]; // captura o que tem após o final da primeira linha
	i = 0;
	j = 0;
	while (buff[j] && buff[j] != '\n')
		str[i++] = buff[j++];
	str[i] = buff[j];
	return (str);
}

char	*save_line(char *saved_line, char *buff, int buff_cnt)
{
	static int	i = 0;
	static char	*teste;
	int			j;
	int			k;

	j = 0;
	k = 0;
	teste = malloc(buff_cnt * sizeof(char));
	while (buff[j] && buff_cnt--)
	{
		saved_line[i] = buff[j];
		if (my_strchr(saved_line, '\n'))
			teste[k++] = buff[j];
		i++;
		j++;
	}
	saved_line[i] = buff[j];
	if (my_strchr(saved_line, '\n'))
		i = 0;
	return (saved_line);
}

char	*get_next_line(int fd)
{	
	char		*buffer;
	static char	*saved_buffer;
	char		*line;
	int			i;

	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	saved_buffer = malloc(1000 * sizeof(char));
	line = "";
	if (!buffer || !saved_buffer)
		return (NULL);
	i = read(fd, buffer, BUFFER_SIZE);
	while (i > 0)
	{	
		saved_buffer = save_line(saved_buffer, buffer, i);
		if (my_strchr(saved_buffer, '\n'))
			break ;
		i = read(fd, buffer, BUFFER_SIZE);
	}
	if (i == 0)
		return (NULL);
	return (str_concat(line, saved_buffer));
}

// Na primeira chamada ele vem certo pois o read está na posição inicial,
// na segunda já vai dar ruim pq o read andou até lá na frente
// preciso pensar em alguma forma de salvar e enviar a primeira linha
// salvar a próxima linha, e se for a última linha inserir 
// caractere nulo no final

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
// 	printf("%s\n", linha);
// 	linha = get_next_line(fileno(arquivo));
// 	printf("%s\n", linha);
// 	linha = get_next_line(fileno(arquivo));
// 	printf("%s\n", linha);
// 	fclose(arquivo);
// 	return (0);
// }
