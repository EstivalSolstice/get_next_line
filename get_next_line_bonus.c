/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:03:05 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/15 23:59:09 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fd_list	*get_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*node;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	return (node->save = NULL, node->next = *head, *head = node, node);
}

void	remove_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*prev;
	t_fd_list	*node;

	node = *head;
	prev = NULL;
	while (node)
	{
		if (node->fd == fd)
		{
			if (prev)
				prev->next = node->next;
			else
				*head = node->next;
			if (node->save)
				free(node->save);
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}

char	*read_and_store(int fd, char **save)
{
	char	*buf;
	char	*tmp;
	int		bytes_read;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(*save, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), free(*save), *save = NULL, (NULL));
		if (bytes_read > 0)
		{
			buf[bytes_read] = '\0';
			tmp = ft_strjoin(*save, buf);
			if (!tmp)
				return (free(buf), free(*save), *save = NULL, (NULL));
			free(*save);
			*save = tmp;
		}
	}
	return (free(buf), *save);
}

char	*extract_line(char **save)
{
	char	*line;
	char	*tmp;
	int		line_length;

	if (!*save || !**save)
		return (NULL);
	line = allocate_and_find_line(*save, &line_length);
	if (!line)
		return (NULL);
	copy_line(line, *save);
	tmp = ft_strdup(*save + line_length);
	if (!tmp)
		return (free(line), NULL);
	return (free(*save), *save = tmp, line);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*head;
	t_fd_list			*current;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = get_fd_node(&head, fd);
	if (!current)
		return (NULL);
	current->save = read_and_store(fd, &current->save);
	if (!current->save)
		return (remove_fd_node(&head, fd), NULL);
	line = extract_line(&current->save);
	if (!line)
		return (remove_fd_node(&head, fd), NULL);
	if (!current->save || !*current->save)
		remove_fd_node(&head, fd);
	return (line);
}
