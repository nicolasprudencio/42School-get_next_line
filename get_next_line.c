/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprudenc <nprudenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:30:45 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/13 19:24:31 by nprudenc         ###   ########.fr       */
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

char	*save_line(int fd, char *line_storage, char *buffer)
{
	int		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{	
		if (!line_storage)
			line_storage = ft_strdup("");
		line_storage = ft_strjoin(line_storage, buffer);
		if (ft_strchr(line_storage, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
	}
	return (line_storage);
}

char	*clean_line(char* line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		str[j++] = line[i++];
	str[j] = line[i];
	return (str);
}

// função para limpar a line, e salvar o início da pŕoxima linha no line_storage
// char	*save_storage(char *line, char *line_storage)
// {	
// 	int	i;

// 	i = 0;
// 	return (line_storage);
// }

char	*get_next_line(int fd)
{	
	char		*buffer;
	static char	*line_storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = save_line(fd, line_storage, buffer);
	free(buffer);
	line_storage = ft_strchr(line, '\n') + 1;
	line = clean_line(line);
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
	printf("%s", linha);
	free(linha);
	linha = get_next_line(fileno(arquivo));
	printf("%s", linha);
	free(linha);
	linha = get_next_line(fileno(arquivo));
	printf("%s", linha);
	free(linha);
	fclose(arquivo);
	return (0);
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