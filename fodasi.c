/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fodasi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprudenc <nprudenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:33:32 by nprudenc          #+#    #+#             */
/*   Updated: 2023/05/30 14:42:24 by nprudenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;
	int			teste;
	int			i;
	int			j;

	buff = malloc(BUFFER_SIZE * sizeof(char));
	line = malloc(100 * sizeof(char));
	if (!buff)
		return (NULL);
	i = 0;
	j = 0;
	teste = read(fd, buff, BUFFER_SIZE);
	while (buff[i] != '\n' && buff[i] != '\0' && teste != 0)
	{	
		line[j] = buff[i];
		if (line[j] == BUFFER_SIZE - 1)
		{	
			teste = read(fd, buff, BUFFER_SIZE);
			i = -1;
		}
		i++;
		j++;
	}
	return (line);
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
	fclose(arquivo);
	return (0);
}
