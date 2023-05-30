/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprudenc <nprudenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:25:20 by nprudenc          #+#    #+#             */
/*   Updated: 2023/05/30 17:45:57 by nprudenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*str;
	int			i;
	int			bytes_read;

	buff = malloc(BUFFER_SIZE * sizeof(char));
	bytes_read = read(fd, buff, BUFFER_SIZE);
	i = 0;
	while (read(fd, buff, BUFFER_SIZE) != 0 && bytes_read != 0)
	{
		str = ft_strjoin(str, buff);
	}
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
	fclose(arquivo);
	return (0);
}
