/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utilities.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:25:52 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/01 14:25:55 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_free(void *token)
{
	free(((t_token *)token)->data);
	free(token);
}

bool	is_quoted_token_start(t_token *token)
{
	int	length;

	length = ft_strlen(token->data);
	return ((token->data[0] == '\'' || token->data[0] == '\"')
		&& token->data[length - 1] != '\'' && token->data[length - 1] != '\"');
}

bool	is_quoted_token_end(t_token *token)
{
	int	length;

	length = ft_strlen(token->data);
	return ((token->data[length - 1] == '\'' || token->data[length - 1] == '\"')
		&& token->data[0] != '\'' && token->data[0] != '\"');
}

t_token	*token_new(char *data, t_token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->data = data;
	token->type = type;
	return (token);
}

t_token	*str_to_token(char *str, t_token *previous_token)
{
	if (ft_strncmp(str, "|", sizeof("|")) == 0)
	{
		return (token_new(str, PIPE_TOKEN));
	}
	if (str_equals(str, "<") || str_equals(str, ">")
		|| str_equals(str, "<<") || str_equals(str, ">>"))
	{
		return (token_new(str, REDIRECTION_TOKEN));
	}
	if (previous_token != NULL
		&& (previous_token->type == OPTION_TOKEN
			|| previous_token->type == CMD_OR_FILE_TOKEN))
	{
		return (token_new(str, OPTION_TOKEN));
	}
	return (token_new(str, CMD_OR_FILE_TOKEN));
}
