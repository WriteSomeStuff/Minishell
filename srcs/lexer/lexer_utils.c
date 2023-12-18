/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 11:31:00 by mstegema      #+#    #+#                 */
/*   Updated: 2023/12/15 18:36:33 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_token_type(t_token *token)
{
	if (ft_strchr(token->data, '>') || ft_strchr(token->data, '<'))
		token->type = RDR_TOKEN;
	else if (ft_strchr(token->data, '|'))
		token->type = PIPE_TOKEN;
	else
		token->type = CMD_TOKEN;
}

t_token	*split_rdrtoken(t_token *token, size_t i)
{
	char	*data;
	size_t	len;
	char	*new_data;
	t_token	*new;

	data = token->data;
	len = ft_strlen(data);
	new_data = NULL;
	new = NULL;
	new_data = ft_substr(data, i + 1, len - i);
	if (!new_data)
		return (NULL);
	new = new_token(new_data);
	if (!new)
		return (free(new_data), NULL);
	init_token_type(new);
	token->data = ft_substr(data, 0, i + 1);
	if (!token->data)
		return (free(new_data), free(data), free(new), NULL);
	init_token_type(token);
	return (free(data), new);
}

size_t	is_splitable(t_token *token)
{
	size_t	i;
	size_t	len;
	char	*data;

	i = 0;
	data = token->data;
	len = ft_strlen(data);
	while (i < len)
	{
		if (((ft_strchr("<", data[i]) != NULL && ft_strchr("<", data[i + 1]) == \
		NULL) || (ft_strchr("<>", data[i]) == NULL && \
		ft_strchr("<>", data[i + 1]) != NULL) || (ft_strchr("|", data[i]) == \
		NULL && ft_strchr("|", data[i + 1]) != NULL) || \
		(ft_strchr("|", data[i]) != NULL && ft_strchr("|", data[i + 1]) == \
		NULL)) && data[i + 1] != '\0')
			break ;
		i++;
	}
	return (i);
}
