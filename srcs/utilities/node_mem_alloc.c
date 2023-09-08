/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_mem_alloc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:29:21 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/01 16:03:06 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rdr	*ft_allocate_mem_rdr(char *data, t_rdr_type type)
{
	t_rdr	*rdr;

	rdr = (t_rdr *)malloc(sizeof(t_rdr));
	if (!rdr)
		return (NULL);
	rdr->data = data;
	rdr->type = type;
	return (rdr);
}

t_cmd	*ft_allocate_mem_cmd(char **arg, t_env *env, bool builtin)
{
	t_cmd	*exec;

	exec = (t_cmd *)malloc(sizeof(t_cmd));
	if (!exec)
		return (NULL);
	exec->arg = arg;
	exec->env = env;
	exec->builtin = builtin;
	exec->path = NULL;
	return (exec);
}

t_token	*new_token(const char *data, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->data = (char *)data;
	token->type = type;
	return (token);
}
