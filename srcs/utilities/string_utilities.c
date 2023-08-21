/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_utilities.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:25:42 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/01 14:25:43 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	str_contains_length(const char *str, int length, char c)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool	str_contains_any(const char *str, const char *chars)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (chars[j] != '\0')
		{
			if (str[i] == chars[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

// returns the amount of characters in the string until one of the given
// delimiters is encountered or the terminating character.
int	str_length_until(char *str, const char *delimiters, int delimiter_count)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (j < delimiter_count)
		{
			if (str[i] == delimiters[j])
				return (i);
			j++;
		}
		i++;
	}
	if (str_contains_length(delimiters, delimiter_count, '\0'))
		return (i);
	return (-1);
}

bool	str_equals(char *lhs, char *rhs)
{
	int	lhs_length;
	int	i;

	lhs_length = ft_strlen(lhs);
	i = 0;
	while (i < lhs_length)
	{
		if (lhs[i] != rhs[i])
			return (false);
		i++;
	}
	if (rhs[i] != '\0')
		return (false);
	return (true);
}

bool	ft_cmpname(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (!n)
		return (false);
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && i <= n)
	{
		i++;
		if (i == n && (s1[i] == '\0' || s1[i] == '=' || s1[i] == '+') && \
			(s2[i] == '\0' || s2[i] == '=' || s2[i] == '+'))
			return (false);
	}
	return (true);
}
