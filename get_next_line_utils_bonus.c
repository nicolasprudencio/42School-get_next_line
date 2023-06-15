/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nprudenc <nprudenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:07:13 by nprudenc          #+#    #+#             */
/*   Updated: 2023/06/15 19:11:12 by nprudenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char	*s)
{	
	int	i;

	i = 0;
	while (s[i])
	{	
		i++;
	}
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	size_max;
	size_t	i;

	i = 0;
	size_max = nmemb * size;
	if (size_max && size_max / size != nmemb)
		return (NULL);
	str = malloc(size_max);
	if (!str)
		return (NULL);
	while (i < size_max)
		str[i++] = 0;
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2) + 1;
	str = (char *)ft_calloc(s1_len + s2_len, sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{	
	int	i;

	i = 0;
	while (s[i])
	{	
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		counter;
	int		i;
	char	*str;

	counter = ft_strlen(s) + 1;
	str = (char *)ft_calloc(counter, sizeof(char));
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
