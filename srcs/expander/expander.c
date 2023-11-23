/* ************************************************************************** */
/*							                                                  */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 12:08:20 by mstegema      #+#    #+#                 */
/*   Updated: 2023/09/06 15:39:23 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expanded_part(char *str, t_env *env)
{
	char	**env_array;
	char	*res;
	size_t	i;
	size_t	len;

	env_array = env->new_env;
	res = NULL;
	i = 0;
	while (env_array[i] != NULL)
	{
		len = ft_strlen(str);
		if (ft_strncmp(env_array[i], str, len) == 0 && env_array[i][len] == '=')
		{
			len = len + 1;
			res = ft_substr(env_array[i], len, ft_strlen(env_array[i]) - len);
			return (free(str), res);
		}
		i++;
	}
	res = ft_strjoin("", "");
	return (free(str), res);
}

char	*expand_data(char *str, t_env *env, bool in_heredoc)
{
	char	*new_data;
	char	*temp;
	char	*beginning;
	char	*middle;
	char	*end;

	beginning = find_begin(str, in_heredoc); //if beginning == str return beginning
	if (!beginning)
		return (NULL);
	end = find_end(str, beginning);
	if (!end)
		return (free(beginning), NULL);
	middle = find_middle(str);
	if (!middle)
		return (free(beginning), free(end), NULL);
	middle = expanded_part(middle, env);
	if (!middle)
		return (free(beginning), free(end), NULL);
	temp = ft_strjoin(beginning, middle);
	if (!temp)
		return (multi_free(beginning, middle, end, NULL), NULL);
	new_data = ft_strjoin(temp, end);
	if (!new_data)
		return (multi_free(beginning, middle, end, temp), NULL);
	return (multi_free(beginning, middle, end, temp), new_data);
}

static size_t	replace_token(t_token *token, t_env *env, t_init *process)
{
	char	*new_data;
	char	*temp;

	if (ft_strncmp(token->data, "$?", 3) == 0)
		new_data = ft_itoa(process->errorcode);
	else if (ft_strncmp(token->data, "~", 2) == 0)
		new_data = expand_data("$HOME", env, false);
	else if (ft_strncmp(token->data, "~/", 2) == 0)
	{
		temp = expand_data("$HOME", env, false);
		if (!temp)
			return (EXIT_FAILURE);
		new_data = ft_strjoin(temp, token->data + 1);
		free(temp);
	}
	else
		new_data = expand_data(token->data, env, false);
	if (!new_data)
		return (EXIT_FAILURE);
	temp = token->data;
	token->data = new_data;
	free(temp);
	return (EXIT_SUCCESS);
}

bool	expand_check(char *str, size_t start)
{
	bool	in_single;
	bool	in_double;
	size_t	i;

	in_single = false;
	in_double = false;
	i = 0;
	while (str[i] != '\0' && i < start)
	{
		if (str[i] == '\'' && in_double == false)
			in_single = !in_single;
		if (str[i] == '\"' && in_single == false)
			in_double = !in_double;
		i++;
	}
	return (!in_single);
}

size_t	expand(t_list *tokens, t_env *env, t_init *process)
{
	t_token	*token;
	size_t	i;

	while (tokens != NULL)
	{
		i = 0;
		token = tokens->content;
		while (token->data != NULL && token->data[i] != '\0')
		{
			if (token->data[i] == '$' || ft_strncmp(token->data, "~", 2) \
			== 0 || ft_strncmp(token->data, "~/", 2) == 0)
			{
				if (expand_check(token->data, i) == true && \
					ft_strncmp(token->data, "$", 2) != 0)
				{
					if (replace_token(token, env, process) == EXIT_FAILURE)
						return (EXIT_FAILURE);
					i = 0;
				}
			}
			i++;
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
