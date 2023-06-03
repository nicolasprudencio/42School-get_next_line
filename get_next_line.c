/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:25:20 by nprudenc          #+#    #+#             */
/*   Updated: 2023/06/03 19:09:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ftt_strlen(const char	*s)
{	
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{	
		i++;
		s++;
	}
	return (i);
}

// int	ftt_strchr(const char *s, int c)
// {
// 	while (*s)
// 	{	
// 		if (*s == (char)c)
// 			return (0);
// 		s++;
// 	}
// 	if ((unsigned char)c)
// 		return (0);
// 	return (1);
// }

int	line_cnt(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*str;
	int			i;
	int			j;
	int			k;

	buff = malloc(BUFFER_SIZE * sizeof(char));
	read(fd, buff, BUFFER_SIZE);
	i = line_cnt(buff);
	str = malloc(i + 1 * sizeof(char));
	if (!str)
		return (NULL);
	printf("line_cnt: %d\n", i);
	j = 0;
	k = 0;
	while (buff[j] && buff[j] != '\n')
		str[k++] = buff[j++];
	str[k] = buff[j];
	free(buff);
	return (str);
}

int	main(void)
{
	FILE	*arquivo;
	char	*linha;

	arquivo = fopen("teste.txt", "r");
	if (!arquivo)
	{
		printf("Erro ao abrir o arquivo.\n");
		return (1);
	}
	linha = get_next_line(fileno(arquivo));
	printf("%s\n", linha);
	linha = get_next_line(fileno(arquivo));
	printf("%s\n", linha);
	linha = get_next_line(fileno(arquivo));
	printf("%s\n", linha);
	fclose(arquivo);
	return (0);
}
