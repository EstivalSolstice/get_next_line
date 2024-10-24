/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:03:25 by joltmann          #+#    #+#             */
/*   Updated: 2024/10/19 12:41:27 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/**
 * @brief Structure to store file descriptor and its corresponding saved data.
 */
typedef struct s_fd_list
{
	int					fd;
	char				*save;
	struct s_fd_list	*next;
}						t_fd_list;

/* -------------------- Main function -------------------- */

/**
 * @brief Reads a line from the given file descriptor.
 *
 * @param fd The file descriptor to read from.
 *
 * @return A pointer to the line read, or NULL if EOF or an error occurs.
 */
char					*get_next_line(int fd);

/**
 * @brief Retrieves or creates a node for the given file descriptor.
 *
 * @param head A double pointer to the head of the file descriptor list.
 * @param fd The file descriptor to retrieve or create a node for.
 *
 * @return A pointer to the node corresponding to the given file descriptor,
 *         or NULL on failure.
 */
t_fd_list				*get_fd_node(t_fd_list **head, int fd);

/**
 * @brief Removes a node corresponding to the given file descriptor.
 *
 * @param head A double pointer to the head of the file descriptor list.
 * @param fd The file descriptor of the node to remove.
 */
void					remove_fd_node(t_fd_list **head, int fd);

/* ---------- Core functions to read and extract lines ---------- */

/**
 * @brief Reads data from the file and stores it in the save buffer.
 *
 * @param fd The file descriptor to read from.
 * @param save A double pointer to the save buffer.
 *
 * @return A pointer to the updated save buffer, or NULL on failure.
 */
char					*read_and_store(int fd, char **save);

/**
 * @brief Extracts a line from the saved buffer.
 *
 * @param save A double pointer to the saved buffer.
 * 
 * @return A pointer to the extracted line, or NULL on failure.
 */
char					*extract_line(char **save);

/**
 * @brief Allocates memory for a line and determines its length.
 *
 * @param save The saved buffer to read from.
 * @param line_length A pointer to store the length of the line.
 * 
 * @return A pointer to the allocated line, or NULL on failure.
 */
char					*allocate_and_find_line(char *save, int *line_length);

/**
 * @brief Copies a line from the saved buffer to the line buffer.
 *
 * @param line The destination buffer to copy the line into.
 * @param save The source saved buffer to copy the line from.
 */
void					copy_line(char *line, char *save);

/* -------------------- Utility functions -------------------- */

/**
 * @brief Joins two strings into one new string.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * 
 * @return A pointer to the newly allocated joined string, or NULL on failure.
 */
char					*ft_strjoin(char *s1, char *s2);

/**
 * @brief Duplicates a string and returns a pointer to the new string.
 *
 * @param s The string to duplicate.
 * 
 * @return A pointer to the newly allocated string, or NULL on failure.
 */
char					*ft_strdup(const char *s);

/**
 * @brief Finds the first occurrence of a character in a string.
 *
 * @param s The string to search.
 * @param c The character to find.
 * @return	A pointer to the first occurrence of the character,
 * 			or NULL if not found.
 */
char					*ft_strchr(const char *s, int c);

#endif