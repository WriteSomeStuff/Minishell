/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atollong.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 13:50:56 by cschabra      #+#    #+#                 */
/*   Updated: 2023/12/19 15:59:05 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	is_whitespace_ll(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\r' || c == '\n'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

static int32_t	skip_white_space_ll(const char *str, int32_t *multiplyer)
{
	int32_t	i;
	char	c;
	int32_t	is_prefixed;

	i = 0;
	is_prefixed = 0;
	c = str[i];
	while ((is_whitespace_ll(c) == 1 || c == '-' || c == '+')
		&& is_prefixed == 0)
	{
		if (c == '-' || c == '+')
		{
			if (c == '-')
				*multiplyer = -1;
			is_prefixed = 1;
		}
		i++;
		c = str[i];
	}
	if (ft_isdigit(c) == 0)
		return (-1);
	return (i);
}

int64_t	ft_atollong(t_list *lst, t_init *process, const char *str)
{
	u_int64_t	result;
	int64_t		return_result;
	int32_t		i;
	int32_t		multiplyer;
	char		c;

	result = 0;
	multiplyer = 1;
	i = skip_white_space_ll(str, &multiplyer);
	if (i == -1)
		return (0);
	c = str[i];
	while (ft_isdigit(c) == 1)
	{
		result += (c - 48);
		if (ft_isdigit(str[i + 1]) == 1)
			result *= 10;
		i++;
		c = str[i];
	}
	if (((result - 1) > LLONG_MAX && multiplyer == -1) \
		|| (result > LLONG_MAX && multiplyer == 1))
		ft_error_exit(lst, process, (char *)str);
	return_result = result * multiplyer;
	return (return_result);
}
