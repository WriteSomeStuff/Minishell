/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 15:12:18 by mstegema      #+#    #+#                 */
/*   Updated: 2023/12/19 16:06:31 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wordcount(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (is_whitespace_ll(s[i]) == 0 && quote_check(s, i) == NOT_QUOTED)
		{
			count++;
			while (s[i] && ((is_whitespace_ll(s[i]) == 0 && quote_check(s, i) \
			== NOT_QUOTED) || quote_check(s, i) > NOT_QUOTED))
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	wordlen(char const *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && ((is_whitespace_ll(s[i]) == 0 && quote_check(s, i) == \
	NOT_QUOTED) || quote_check(s, i) > NOT_QUOTED))
	{
		len++;
		i++;
	}
	return (len);
}

static char	**free_array(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		array[j] = NULL;
		j--;
	}
	free(array);
	array = NULL;
	return (NULL);
}

char	**lexer_split(char const *s)
{
	int		i;
	int		j;
	int		strings;
	int		len;
	char	**res;

	i = 0;
	j = 0;
	strings = wordcount(s);
	res = (char **)ft_calloc(strings + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (j < strings)
	{
		while (is_whitespace_ll(s[i]) == 1)
			i++;
		len = wordlen(s, i);
		res[j] = ft_substr(s, i, len);
		if (!res[j])
			return (free_array(res, j));
		i += len;
		j++;
	}
	res[j] = 0;
	return (res);
}
