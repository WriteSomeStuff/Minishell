// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   expander.c                                         :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/08/01 14:24:07 by cschabra      #+#    #+#                 */
// /*   Updated: 2023/08/24 15:24:13 by mstegema      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// static bool	check_environment_variable_length(t_expand_length_info *info)
// {
// 	if ((info->dquote_i == -1 && info->quote_i == -1) \
// 	|| info->dquote_i < info->quote_i)
// 	{
// 		info->i = resolve_environment_variable_length(\
// 		&(info->data[info->i + 1]), &info->length);
// 		if (info->i == -1)
// 			return (false);
// 	}
// 	else
// 	{
// 		info->length++;
// 	}
// 	return (true);
// }

// static int	determine_expand_data_length(char *data)
// {
// 	t_expand_length_info	info;

// 	init_expand_length_info(&info, data);
// 	while (!expand_length_data_at(info, '\0'))
// 	{
// 		if (expand_length_data_at(info, '$'))
// 		{
// 			if (!check_environment_variable_length(&info))
// 				return (-1);
// 		}
// 		else if (expand_length_data_at(info, '\''))
// 		{
// 			update_quote(&info);
// 		}
// 		else if (expand_length_data_at(info, '\"'))
// 		{
// 			update_dquote(&info);
// 		}
// 		else
// 		{
// 			info.length++;
// 		}
// 		info.i++;
// 	}
// 	return (info.length);
// }

// static char	*create_expanded_data(char *old_data, int length)
// {
// 	t_expand_info	info;

// 	if (!init_expand_info(&info, old_data, length))
// 		return (NULL);
// 	while (!expand_data_at(info, '\0'))
// 	{
// 		if (expand_data_at(info, '$'))
// 		{
// 			if (!check_env_variable_assignment(&info))
// 				return (free(info.expanded_data), NULL);
// 		}
// 		else if (expand_data_at(info, '\''))
// 			check_quote_index_at_data_index(&info);
// 		else if (expand_data_at(info, '\"'))
// 			check_dquote_index_at_data_index(&info);
// 		else
// 		{
// 			info.expanded_data[info.j] = info.old_data[info.i];
// 			info.j++;
// 		}
// 		info.i++;
// 	}
// 	info.expanded_data[info.j] = '\0';
// 	return (info.expanded_data);
// }

// bool	expand_data(t_token *token, t_token *previous_token)
// {
// 	int		expand_data_length;
// 	bool	expandable;
// 	char	*old_data;

// 	if (token->type == RDR_TOKEN || token->type == PIPE_TOKEN
// 		|| is_here_doc_argument(token, previous_token))
// 		return (true);
// 	expand_data_length = determine_expand_data_length(token->data);
// 	expandable = str_contains_any(token->data, "$\"\'");
// 	if (expandable)
// 	{
// 		old_data = token->data;
// 		token->data = create_expanded_data(old_data, expand_data_length);
// 		if (token->data == NULL)
// 			return (free(old_data), false);
// 		free(old_data);
// 	}
// 	return (true);
// }

// bool	expand_tokens(t_list *tokens)
// {
// 	t_list	*current;
// 	t_token	*current_token;
// 	t_token	*previous_token;

// 	previous_token = NULL;
// 	current = tokens;
// 	while (current != NULL)
// 	{
// 		current_token = (t_token *)current->content;
// 		if (!expand_data(current_token, previous_token))
// 			return (false);
// 		previous_token = current_token;
// 		current = current->next;
// 	}
// 	return (true);
// }

// // 1. ook $? afhandelen
// // (nadat de implementatie hiervoor is gemaakt bij de executor)
// // int	main(void)
// // {
// // 	t_list	*tokens;

// // 	tokens = read_tokens_from_command_line("echo \"hallo $onzin\"");
// // 	expand_tokens(tokens);
// // 	ft_lstclear(&tokens, &token_free);
// // 	system("leaks -q minishell");
// // }
