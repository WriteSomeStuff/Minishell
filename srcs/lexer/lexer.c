/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:10:44 by mstegema      #+#    #+#                 */
/*   Updated: 2023/09/06 19:54:40 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	split_rdrtokens(t_list *tokens)
{
	t_token	*token;
	t_list	*next;
	t_token	*new;
	t_list	*new_node;

	while (tokens != NULL)
	{
		token = tokens->content;
		next = tokens->next;
		new = NULL;
		if (token->type == RDR_TOKEN)
			new = is_splitable(token);
		if (new)
		{
			new_node = ft_lstnew(new);
			tokens->next = new_node;
			new_node->next = next;
		}
		tokens = tokens->next;
	}
	return (0);
}

static size_t	merge_tokens(t_list *tokens)
{
	t_list	*begin;
	t_list	*end;

	while (tokens != NULL)
	{
		begin = quote_begin(tokens);
		if (begin == NULL)
			return (1);
		end = quote_end(begin);
		if (end == NULL)
			return (1);
		tokens = begin;
		join_datastr(tokens, end);
		begin->next = end->next;
		tokens = tokens->next;
	}
	return (0);
}

static size_t	make_tlist(const char **ui_array, t_list **tokens)
{
	t_list	*node;
	t_token	*token;
	char	*str;

	while (ui_array[0] != NULL)
	{
		str = (char *)*ui_array;
		token = init_token(str);
		if (token == NULL)
			return (ft_lstclear(tokens, &free), 1);
		node = ft_lstnew(token);
		if (node == NULL)
			return (ft_lstclear(tokens, &free), 1);
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
		exit(1);
	make_tlist((const char **) ui_array, &tokens);
	merge_tokens(tokens);
	split_rdrtokens(tokens);
	return (tokens);
}
