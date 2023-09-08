/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 11:31:00 by mstegema      #+#    #+#                 */
/*   Updated: 2023/09/06 15:05:40 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*is_splitable(t_token *token)
{
	char	*data;
	char	*new_data;
	size_t	len;
	t_token	*new;

	data = token->data;
	new_data = NULL;
	len = ft_strlen(data);
	new = NULL;
	if (len > 2 && ft_strchr("<>", data[0]) && ft_strchr("<>", data[1]) \
	&& ft_strchr("<>", data[2]) == NULL)
		new_data = ft_substr(data, 2, len);
	else if (len > 1 && ft_strchr("<>", data[0]) \
	&& ft_strchr("<>", data[1]) == NULL)
		new_data = ft_substr(data, 1, len);
	if (new_data)
		new = new_token(new_data, CMD_OR_FILE_TOKEN);
	return (new);
}

size_t	join_datastr(t_list *tokens, t_list *end)
{
	t_token	*token;
	t_token	*next_token;
	char	*temp;

	token = tokens->content;
	while (tokens != end)
	{
		next_token = tokens->next->content;
		temp = ft_strjoin(token->data, " ");
		free(token->data);
		token->data = ft_strjoin(temp, next_token->data);
		free(temp);
		free(next_token->data);
		tokens = tokens->next;
	}
	return (0);
}

t_list	*quote_end(t_list *tokens)
{
	t_token	*token;
	size_t	i;
	char	delim;

	token = tokens->content;
	while (tokens != NULL)
	{
		i = 0;
		token = tokens->content;
		while (token->data[i] != '\0')
		{
			if ((token->data[i] == '\'' || token->data[i] == '\"') \
			&& delim == 0)
				delim = token->data[i];
			else if (token->data[i] == delim)
				return (tokens);
			i++;
		}
		tokens = tokens->next;
	}
	return (NULL);
}

t_list	*quote_begin(t_list *tokens)
{
	t_token	*token;
	size_t	i;

	while (tokens != NULL)
	{
		i = 0;
		token = tokens->content;
		while (token->data[i] != '\0')
		{
			if (token->data[i] == '\'' || token->data[i] == '\"')
				return (tokens);
			i++;
		}
		tokens = tokens->next;
	}
	return (NULL);
}

t_token	*init_token(const char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (new_token(str, PIPE_TOKEN));
	else if ((ft_strncmp(str, ">", 1) == 0) || (ft_strncmp(str, "<", 1) == 0)
		|| (ft_strncmp(str, ">>", 2) == 0) || (ft_strncmp(str, "<<", 2) == 0))
		return (new_token(str, RDR_TOKEN));
	else
		return (new_token(str, CMD_OR_FILE_TOKEN));
}
