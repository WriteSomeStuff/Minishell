/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/08 16:23:16 by mstegema      #+#    #+#                 */
/*   Updated: 2023/11/24 14:32:38 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_end(char *str, char *beginning)
{
	char	*end;
	size_t	i;
	size_t	len;

	i = 0;
	while (str[i] == beginning[i])
		i++;
	if (str[i] == '$')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != '?')
			break ;
		i++;
	}
	len = ft_strlen(&str[i]);
	end = ft_substr(str, i, len);
	return (end);
}

char	*find_middle(char *str)
{
	char	*middle;
	size_t	i;
	size_t	len;

	i = 0;
	len = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != ' ')
		{
			while (str[i + len] != '\0')
			{
				if (ft_isalnum(str[i + len]) == 0 && str[i + len] != '_' \
				&& str[i + len] != '?')
					break ;
				len++;
			}
			if (ft_isalnum(str[i + len]) == 0 && str[i + len] != '_')
				break ;
		}
		i++;
	}
	middle = ft_substr(str, i + 1, len - 1);
	return (middle);
}

char	*find_begin(char *str, bool in_heredoc)
{
	char	*beginning;
	size_t	i;

	i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != ' ')
		{
			if (in_heredoc == false)
			{
				if (expand_check(str, i) == true)
					break ;
			}
			else
				break ;
		}
		i++;
	}
	beginning = ft_substr(str, 0, i);
	return (beginning);
}

void	multi_free(char *begin, char *mid, char *end, char *temp)
{
	if (begin)
		free(begin);
	if (mid)
		free(mid);
	if (end)
		free(end);
	if (temp)
		free(temp);
}
