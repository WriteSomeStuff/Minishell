/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_utilities.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:25:42 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/07 12:48:08 by cheyennesch   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	str_equals(char *lhs, char *rhs)
{
	int32_t	lhs_length;
	int32_t	i;

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

bool	ft_cmpname(const char *s1, const char *s2, int32_t n)
{
	int32_t	i;

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
