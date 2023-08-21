/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:24:50 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/16 13:06:06 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	free(cmd);
}

t_cmd	*alloc_cmd(t_list *tokens, t_env *env)
{
	t_cmd	*cmd;

	if (ft_lstsize(tokens) == 0)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->env = env;
	return (cmd);
}

bool	add_cmd_node(t_list *cmd_tokens, t_list **cmds, t_env *env)
{
	t_cmd	*cmd;
	t_list	*cmd_item;

	cmd = alloc_cmd(cmd_tokens, env);
	if (cmd == NULL)
		return (false);
	cmd_item = ft_lstnew(cmd);
	if (cmd_item == NULL)
		return (free_cmd(cmd), false);
	ft_lstadd_back(cmds, cmd_item);
	return (true);
}

bool	parse_tokens(t_list *tokens, t_list *cmds, t_env *env)
{
	t_list	*current;
	t_list	*cmd_tokens;
	t_list	*cmd_token;
	t_token	*token;

	cmd_tokens = NULL;
	current = tokens;
	while (current != NULL)
	{
		token = (t_token *)current->content;
		if (token->type == PIPE_TOKEN)
		{
			if (!add_cmd_node(cmd_tokens, &cmds, env))
				return (lst_free(&cmd_tokens), false);
			lst_free(&cmd_tokens);
		}
		else
		{
			cmd_token = ft_lstnew(token);
			if (cmd_token == NULL)
				return (lst_free(&cmd_tokens), false);
			ft_lstadd_back(&cmd_tokens, cmd_token);
		}
		current = current->next;
	}
	if (ft_lstsize(cmd_tokens) != 0)
	{
		ft_put_token_lst(cmd_tokens);
		if (!add_cmd_node(cmd_tokens, &cmds, env))
			return (lst_free(&cmd_tokens), false);
		lst_free(&cmd_tokens);
	}
	return (true);
}
