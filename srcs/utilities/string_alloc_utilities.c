/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_alloc_utilities.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:25:29 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/01 14:25:31 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// allocates memory for a new string that is cut from the start of given string 
// ending at the index of one of delimiter characters.
char	*str_head(char *str, const char *delimiters, int delimiter_count)
{
	char	*head;
	int		i;
	int		length;

	length = str_length_until(str, delimiters, delimiter_count);
	if (length == -1)
		return (NULL);
	head = (char *)malloc(sizeof(char) * (length + 1));
	if (head == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		head[i] = str[i];
		i++;
	}
	head[i] = '\0';
	return (head);
}

char	*str_join_sep(char *lhs, char *rhs, char c)
{
	char	*joined;
	int		i;
	size_t	lhslen;
	size_t	rhslen;

	lhslen = ft_strlen(lhs);
	rhslen = ft_strlen(rhs);
	joined = (char *)malloc((lhslen + rhslen + 2) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	i = 0;
	while (lhs[i] != '\0')
	{
		joined[i] = lhs[i];
		i++;
	}
	joined[i] = c;
	i++;
	while (rhs[i - lhslen - 1] != '\0')
	{
		joined[i] = rhs[i - lhslen - 1];
		i++;
	}
	joined[i] = '\0';
	return (joined);
}

char	*str_empty(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}
