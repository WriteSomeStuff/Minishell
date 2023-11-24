/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prelim_parser.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 15:55:15 by mstegema      #+#    #+#                 */
/*   Updated: 2023/11/24 13:28:51 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	userinput_check(char c, char *user_input)
{
	bool	res;

	res = false;
	if (c == '\'' && ft_strchr(user_input, '\'') != NULL)
		res = true;
	else if (c == '\"' && ft_strchr(user_input, '\"') != NULL)
		res = true;
	else if (c == '|' && ft_strlen(user_input) > 0)
		res = true;
	return (res);
}

static char	*new_userinput2(char *temp, char *user_input, char c)
{
	char	*rl;

	while (1)
	{
		if (c == '|')
			temp = ft_strjoin(user_input, " ");
		else
			temp = ft_strjoin(user_input, "\n");
		free(user_input);
		if (!temp)
			return (NULL);
		rl = readline("> ");
		if (!rl)
			return (ft_putendl_fd("BabyBash: unexpected end of file", \
				STDERR_FILENO), free(temp), ft_calloc(1, sizeof(char)));
		user_input = ft_strjoin(temp, rl);
		free(temp);
		free(rl);
		if (!user_input)
			return (NULL);
		if (userinput_check(c, user_input) == true)
			break ;
	}
	return (user_input);
}

static char	*new_userinput(char *input, char c)
{
	char	*user_input;
	char	*temp;

	temp = NULL;
	user_input = ft_calloc(1, sizeof(char));
	if (!user_input)
		return (NULL);
	user_input = new_userinput2(temp, user_input, c);
	if (!user_input)
		return (NULL);
	if (user_input[0] == '\0')
		return (free(input), user_input);
	temp = ft_strjoin(input, user_input);
	if (!temp)
		return (free(input), free(user_input), NULL);
	return (free(input), free(user_input), temp);
}

static size_t	needs_closing(char *input, char c, size_t start)
{
	size_t	i;
	size_t	count;

	i = start;
	count = 0;
	while (input[i] != '\0')
	{
		if ((input[i] == c && i == 0) || \
			(input[i] == c && input[i - 1] != '\\'))
			count++;
		if (count == 2)
			return (i);
		i++;
	}
	if (count == 1)
		return (0);
	return (i);
}

static char	*close_quotes(char *input)
{
	size_t	i;
	size_t	check;
	char	c;

	i = 0;
	check = 0;
	while (input[i] != '\0')
	{
		c = '0';
		if (input[i] == '\'')
			c = '\'';
		else if (input[i] == '\"')
			c = '\"';
		if (c != '0')
		{
			check = needs_closing(input, c, i);
			if (check == 0)
				return (new_userinput(input, c));
			i = check;
		}
		i++;
	}
	return (input);
}

char	*complete_input(t_init *process, char *input)
{
	size_t	len;

	input = close_quotes(input);
	if (!input)
		return (ft_throw_error(process, ENOMEM), NULL);
	len = ft_strlen(input);
	if (!len)
		return (input);
	if ((input[len - 1] == '|' && input[len - 2] != '\\') || \
		(input[len - 2] == '|' && input[len - 3] != '\\'))
		input = new_userinput(input, '|');
	if (!input)
		return (ft_throw_error(process, ENOMEM), NULL);
	return (input);
}
