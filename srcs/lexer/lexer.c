/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:10:44 by mstegema      #+#    #+#                 */
/*   Updated: 2023/11/23 12:53:01 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	split_rdrtokens(t_list *tokens, size_t i)
{
	t_list	*next;
	t_token	*new;
	t_list	*new_node;

	while (tokens != NULL)
	{
		next = tokens->next;
		if (((t_token *)(tokens->content))->type == RDR_TOKEN)
		{
			i = is_splitable((t_token *)(tokens->content));
			if (i < ft_strlen(((t_token *)(tokens->content))->data))
			{
				new = split_rdrtoken((t_token *)(tokens->content), i);
				if (!new)
					return (EXIT_FAILURE);
				new_node = ft_lstnew(new);
				if (!new_node)
					return (free(new), EXIT_FAILURE);
				tokens->next = new_node;
				new_node->next = next;
			}
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

// static size_t	split_rdrtokens(t_list *tokens)
// {
// 	t_list	*next;
// 	t_token	*token;
// 	t_token	*new;
// 	t_list	*new_node;

// 	while (tokens != NULL)
// 	{
// 		token = tokens->content;
// 		next = tokens->next;
// 		new = NULL;
// 		if (token->type == RDR_TOKEN)
// 		{
// 			new = is_splitable(token, token->data, ft_strlen(token->data), 0);
// 			if (new)
// 			{
// 				new_node = ft_lstnew(new);
// 				tokens->next = new_node;
// 				new_node->next = next;
// 			}
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }

static size_t	merge_tokens(t_list *tokens)
{
	t_list	*begin;
	t_list	*end;

	while (tokens != NULL)
	{
		begin = quote_begin(tokens);
		if (begin == NULL)
			return (EXIT_SUCCESS);
		end = quote_end(begin);
		if (end == NULL)
			return (EXIT_SUCCESS);
		tokens = begin;
		if (join_datastr(tokens, end) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		begin->next = end->next;
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

// is quoted function OR merge befor token initialization and THEN init

// static t_token	*init_token(char *str)
// {
// 	if (ft_strncmp(str, "|", 2) == 0)
// 	{
// 		free(str);
// 		return (new_token(NULL, PIPE_TOKEN));
// 	}
// 	else if ((ft_strchr(str, '>') != NULL) || (ft_strchr(str, '<') != NULL))
// 		return (new_token(str, RDR_TOKEN));
// 	else
// 		return (new_token(str, CMD_TOKEN));
// }

static void	init_token(t_list *tokens)
{
	t_token	*token;

	token = NULL;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (ft_strncmp(token->data, "|", 2) == 0)
			token->type = PIPE_TOKEN;
		else if (ft_strchr(token->data, '\"') == NULL && \
				ft_strchr(token->data, '\'') == NULL && \
				((ft_strchr(token->data, '>') != NULL) || \
				(ft_strchr(token->data, '<') != NULL)) && \
				(ft_strncmp(token->data, "\\<", 3) != 0))
			token->type = RDR_TOKEN;
		else
			token->type = CMD_TOKEN;
		tokens = tokens->next;
	}
}

static size_t	make_tlist(const char **ui_array, t_list **tokens)
{
	t_list	*node;
	t_token	*token;
	char	*str;

	while (ui_array[0] != NULL)
	{
		str = (char *)*ui_array;
		token = new_token(str);
		if (token == NULL)
			return (free_tokenlst(*tokens), 1);
		node = ft_lstnew(token);
		if (node == NULL)
			return (free_tokenlst(*tokens), 1);
		ft_lstadd_back(tokens, node);
		ui_array++;
	}
	return (0);
}

t_list	*tokenisation(const char *user_input)
{
	t_list	*tokens;
	char	**ui_array;

	tokens = NULL;
	ui_array = ft_split(user_input, ' ');
	if (!ui_array)
		return (NULL);
	if (make_tlist((const char **) ui_array, &tokens) == 1)
		return (free(ui_array), NULL);
	free(ui_array);
	if (merge_tokens(tokens) == EXIT_FAILURE)
		return (free_tokenlst(tokens), NULL);
	init_token(tokens);
	if (split_rdrtokens(tokens, 0) == EXIT_FAILURE)
		return (free_tokenlst(tokens), NULL);
	return (tokens);
}
