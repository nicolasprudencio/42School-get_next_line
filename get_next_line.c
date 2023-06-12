/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprudenc <nprudenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:30:45 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/12 15:23:34 by nprudenc         ###   ########.fr       */
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
	return (NULL);
}

// char	*ft_strdup(const char *s)
// {
// 	int		counter;
// 	int		i;
// 	char	*str;

// 	counter = ft_strlen(s) + 1;
// 	str = malloc(counter * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		str[i] = s[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

char	*str_concat(char *str, char *buff)
{	
	static char	*next_line;
	int			i;
	int			j;

	str = malloc(line_cnt(buff) + 1 * sizeof(char));
	if (my_strchr(buff, '\n'))
	{
		next_line = malloc(line_cnt(my_strchr(buff, '\n') + 1) * sizeof(char));
		next_line = my_strchr(buff, '\n');
	}
	if (!str || !next_line)
		return (NULL);
	next_line = my_strchr(buff, '\n');
	i = 0;
	j = 1;
	if (next_line)
		while (next_line[j] && next_line[j] != '\n')
			str[i++] = next_line[j++];
	j = 0;
	while (buff[j] && buff[j] != '\n')
		str[i++] = buff[j++];
	str[i] = buff[j];
	free (buff);
	return (str);
}

char	*save_line(char *saved_line, char *buff, int buff_cnt)
{
	static int	i = 0;
	int			j;

	j = 0;
	while (buff[j] && buff_cnt--)
		saved_line[i++] = buff[j++];
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
	return (str_concat(line, saved_buffer));
}

/*
	2 Problemas para resolver:

	1 - saved_line não foi mallocado e por conta disso
	quando tentamos acessar seu local na memória na função
	save_line,	obtemos um segmentation fault. (resolver)

	2 - De acordo com a regra do nosso while, a função
	read vai ler sem parar até o final do arquivo. Isso
	esta realmente correto? (possível solução, implementar strchr
	para checar o saved_buffer) -> após isso chamar o str_concat
	com as configurações para devolver uma string limpa. (resolvido)

	3 - Encontrar alguma forma de salvar o inicio da próxima linha, e
	quando a get_next_line for chamada novamente, retornar a próxima
	contendo seu inicío anteriormente salvo (resolver)
	|
	|-> possível solucão usar strchr para devolver uma string a partir
		dos caractéres previamente lidos da próx linha (nesse caso estaremos
		devolvendo todo o restante do texto de nosso arquivo)
*/

// line_cnt -> função para contar todos os caracteres de uma linha

// Variável buffer -> armazena o que foi lido do read
// Variável estática saved_buffer -> armazena o que foi lido do buffer
// concatenando até encontrar o primeiro \n
// Variável line -> armazena e concatena tudo do saved_buffer
// até o primeiro \n ou \0

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
// 	printf("%s", linha);
// 	fclose(arquivo);
// 	return (0);
// }
