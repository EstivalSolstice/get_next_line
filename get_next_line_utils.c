/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:03:05 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/27 19:51:01 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*allocate_and_find_line(char *save, int *line_length)
{
	int		length;
	char	*line;

	if (!save || !line_length)
		return (NULL);
	length = 0;
	while (save[length] && save[length] != '\n')
		length++;
	if (save[length] == '\n')
		length++;
	*line_length = length;
	line = malloc(length + 1);
	if (!line)
		return (NULL);
	return (line);
}

void	copy_line(char *line, char *save)
{
	int	i;

	if (!line || !save)
		return ;
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1)
		return (ft_gnl_strdup(s2));
	if (!s2)
		return (ft_gnl_strdup(s1));
	len1 = 0;
	len2 = 0;
	while (s1[len1] != '\0')
		len1++;
	while (s2[len2] != '\0')
		len2++;
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (i < len1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	return (joined[i] = '\0', joined);
}

char	*ft_gnl_strdup(const char *src)
{
	int		index;
	int		len;
	char	*dst;

	index = 0;
	len = 0;
	if (!src)
		return (NULL);
	while (src[len])
		len++;
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	return (dst[index] = '\0', dst);
}

char	*ft_gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
