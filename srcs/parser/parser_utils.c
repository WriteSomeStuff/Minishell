/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 17:15:46 by mstegema      #+#    #+#                 */
/*   Updated: 2023/08/29 15:00:43 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_cmdtokens(t_list **tokens)
{
	t_list	*current;
	t_token	*token;
	size_t	count;

	current = *tokens;
	token = current->content;
	count = 0;
	while (token->type == CMD_OR_FILE_TOKEN && current != NULL)
	{
		token = current->content;
		if (token->type == CMD_OR_FILE_TOKEN)
			count++;
		current = current->next;
	}
	return (count);
}

bool	is_builtin(t_list **tokens)
{
	t_list	*current;
	t_token	*token;
	char	*str;

	current = *tokens;
	token = current->content;
	str = token->data;
	if ((ft_strncmp(str, "echo", 5) == 0) || (ft_strncmp(str, "cd", 3) == 0) \
	|| (ft_strncmp(str, "pwd", 4) == 0) || (ft_strncmp(str, "export", 7) == 0) \
	|| (ft_strncmp(str, "unset", 6) == 0) || (ft_strncmp(str, "env", 4) == 0) \
	|| (ft_strncmp(str, "exit", 5) == 0))
		return (true);
	return (false);
}
