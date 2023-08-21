/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:24:43 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/18 13:59:49 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*find_item_ending_with_quote(t_list *tokens)
{
	t_list	*current;
	t_token	*token;
	int		length;

	current = tokens;
	while (current != NULL)
	{
		token = (t_token *)current->content;
		length = ft_strlen(token->data);
		if (is_quoted_token_end(token))
			return (current);
		current = current->next;
	}
	return (NULL);
}

static bool	merge_quoted_tokens(t_list *tokens)
{
	t_list	*current;
	t_list	*item_ending_in_quote;
	t_token	*token;
	char	*old_token_data;
	char	*data_to_join;

	current = tokens;
	while (current != NULL)
	{
		token = (t_token *)current->content;
		if (is_quoted_token_start(token))
		{
			item_ending_in_quote = find_item_ending_with_quote(current->next);
			if (item_ending_in_quote == NULL)
				return (printf("no closing quotes found\n"), false);
			old_token_data = token->data;
			data_to_join = ((t_token *)item_ending_in_quote->content)->data;
			token->data = str_join_sep(token->data, data_to_join, ' ');
			current->next = item_ending_in_quote->next;
			free(old_token_data);
			ft_lstdelone(item_ending_in_quote, &token_free);
		}
		current = current->next;
	}
	return (true);
}

static t_list	*create_token_list_item(char *token_string, t_list *previous)
{
	t_list	*token_list_item;
	t_token	*token;
	t_token	*previous_token;

	if (previous == NULL)
		previous_token = NULL;
	else
		previous_token = (t_token *)previous->content;
	token = str_to_token(token_string, previous_token);
	if (token == NULL)
		return (NULL);
	token_list_item = ft_lstnew(token);
	if (token_list_item == NULL)
		return (free(token), NULL);
	return (token_list_item);
}

static t_list	*create_token_list_items(char **split_command_line, int length)
{
	t_list	*tokens;
	t_list	*token;
	t_list	*previous;
	int		i;

	i = 0;
	tokens = NULL;
	previous = NULL;
	while (i < length)
	{
		token = create_token_list_item(split_command_line[i], previous);
		if (token == NULL)
			return (ft_lstclear(&tokens, &free), NULL);
		ft_lstadd_back(&tokens, token);
		previous = token;
		i++;
	}
	return (tokens);
}

t_list	*read_tokens_from_command_line(char *command_line)
{
	t_list	*tokens;
	char	**split_command_line;
	int		length;

	split_command_line = ft_split(command_line, ' ');
	if (split_command_line == NULL)
		return (NULL);
	length = str_array_length(split_command_line);
	tokens = create_token_list_items(split_command_line, length);
	if (tokens == NULL)
		return (str_array_free(split_command_line), NULL);
	free(split_command_line);
	if (!merge_quoted_tokens(tokens))
		return (ft_lstclear(&tokens, &token_free), NULL);
	return (tokens);
}
