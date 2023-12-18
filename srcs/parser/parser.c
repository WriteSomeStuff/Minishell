/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:24:50 by cschabra      #+#    #+#                 */
/*   Updated: 2023/12/18 15:58:07 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_scmd_list	*init_cmdstruct(t_list *tokens, t_init *process, size_t i)
{
	t_token	*token;
	t_cmd	*cmd;
	char	**data;
	bool	builtin;

	builtin = is_builtin(&tokens);
	data = ft_calloc(process->arg_count + 1, sizeof(char *));
	if (!data)
		return (NULL);
	while (i < process->arg_count && tokens != NULL)
	{
		token = tokens->content;
		if (token->type == CMD_TOKEN)
			data[i++] = token->data;
		else if (token->type == RDR_TOKEN && \
		((t_token *)(tokens->next->content))->type != RDR_TOKEN)
			tokens = tokens->next;
		if (tokens != NULL)
			tokens = tokens->next;
	}
	cmd = ft_allocate_mem_cmd(data, process->env, builtin);
	if (!cmd)
		return (free(data), NULL);
	return (ft_lstnewscmd(cmd, CMD, process));
}

static t_scmd_list	*init_rdrstruct(t_list *tokens, t_init *process)
{
	t_rdr	*rdr;
	t_token	*token;
	t_token	*next_token;
	char	*str;

	str = "BabyBash: syntax error near unexpected token";
	rdr = NULL;
	token = tokens->content;
	if (tokens->next)
		next_token = tokens->next->content;
	if (tokens->next == NULL || next_token->type != CMD_TOKEN)
		return (ft_putendl_fd(str, STDERR_FILENO), NULL);
	if (ft_strncmp(token->data, ">>", 3) == 0)
		rdr = ft_allocate_mem_rdr(next_token->data, RDR_APPEND);
	else if (ft_strncmp(token->data, "<<", 3) == 0)
		rdr = ft_allocate_mem_rdr(next_token->data, HERE_DOC);
	else if (ft_strncmp(token->data, ">", 2) == 0)
		rdr = ft_allocate_mem_rdr(next_token->data, RDR_OUTPUT);
	else if (ft_strncmp(token->data, "<", 2) == 0)
		rdr = ft_allocate_mem_rdr(next_token->data, RDR_INPUT);
	else
		return (ft_putendl_fd(str, STDERR_FILENO), NULL);
	if (!rdr)
		return (process->must_exit = true, NULL);
	return (ft_lstnewscmd(rdr, RDR, process));
}

t_list	*scmdlist2(t_list *tokens, t_scmd_list **scmds, t_init *process)
{
	t_scmd_list	*node;

	if (((t_token *)(tokens->content))->type == CMD_TOKEN \
		&& process->arg_count == 0)
	{
		process->arg_count = count_cmdtokens(&tokens);
		node = init_cmdstruct(tokens, process, 0);
		if (!node)
			return (freescmdlst_nodata(scmds), process->must_exit = true, NULL);
		scmdlst_add_back(scmds, node);
		while (tokens && ((t_token *)(tokens->content))->type == CMD_TOKEN)
			tokens = tokens->next;
	}
	else if (((t_token *)(tokens->content))->type == CMD_TOKEN \
		&& process->arg_count > 0)
		tokens = tokens->next;
	else if (((t_token *)(tokens->content))->type == RDR_TOKEN)
	{
		node = init_rdrstruct(tokens, process);
		if (!node)
			return (freescmdlst_nodata(scmds), NULL);
		tokens = tokens->next->next;
		scmdlst_add_back(scmds, node);
	}
	return (tokens);
}

static t_list	*make_cmdlist(t_list *tokens, t_list **cmds, t_init *process)
{
	t_list		*node;
	t_scmd_list	*scmds;

	node = NULL;
	scmds = NULL;
	while (tokens)
	{
		tokens = make_scmdlist(tokens, &scmds, process);
		if (process->must_exit == true)
			return (freelst_nodata(*cmds), NULL);
		if (!scmds)
		{
			process->errorcode = 2;
			return (freelst_nodata(*cmds), NULL);
		}
		node = ft_lstnew(scmds);
		if (!node)
			return (process->must_exit = true, freelst_nodata(*cmds), NULL);
		scmds = NULL;
		ft_lstadd_back(cmds, node);
		if (tokens == NULL)
			return (*cmds);
		tokens = tokens->next;
	}
	return (*cmds);
}

t_list	*parse(t_env *env, t_init *process, const char *user_input)
{
	t_list	*tokens;
	t_list	*cmds;

	tokens = tokenisation(user_input);
	if (!tokens)
	{
		process->must_exit = true;
		return (ft_throw_error(process, ENOMEM), NULL);
	}
	if (expand(tokens, env, process) == EXIT_FAILURE || \
		remove_quotes(tokens) == EXIT_FAILURE)
	{
		process->must_exit = true;
		return (ft_throw_error(process, ENOMEM), free_tokenlst(&tokens, true), \
			NULL);
	}
	cmds = NULL;
	cmds = make_cmdlist(tokens, &cmds, process);
	if (!cmds)
	{
		if (process->must_exit == true)
			ft_throw_error(process, ENOMEM);
		return (free_tokenlst(&tokens, true), NULL);
	}
	return (free_tokenlst(&tokens, false), cmds);
}
