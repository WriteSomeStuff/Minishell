// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   expand_info.c                                      :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/08/01 14:23:39 by cschabra      #+#    #+#                 */
// /*   Updated: 2023/08/01 14:23:41 by cschabra      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// bool	expand_data_at(t_expand_info info, char c)
// {
// 	return (info.old_data[info.i] == c);
// }

// bool	init_expand_info(t_expand_info *info, char *old_data, \
// int expand_data_length)
// {
// 	info->i = 0;
// 	info->j = 0;
// 	info->dquote_i = -1;
// 	info->quote_i = -1;
// 	info->old_data = old_data;
// 	info->expanded_data = (char *)malloc(sizeof(char) * expand_data_length);
// 	return (info->expanded_data != NULL);
// }

// bool	check_env_variable_assignment(t_expand_info *info)
// {
// 	if ((info->quote_i == -1) || info->dquote_i < info->quote_i)
// 	{
// 		if (!do_env_variable_assignment(&(info->old_data[info->i + 1]), \
// 		&(info->expanded_data[info->j]), &info->i, &info->j))
// 			return (false);
// 	}
// 	else
// 	{
// 		info->expanded_data[info->j] = info->old_data[info->i];
// 		info->j++;
// 	}
// 	return (true);
// }

// void	check_quote_index_at_data_index(t_expand_info *info)
// {
// 	info->quote_i = resolve_quote_index_at_data_index(info->i, info->quote_i);
// 	if (info->dquote_i != -1)
// 	{
// 		info->expanded_data[info->j] = info->old_data[info->i];
// 		info->j++;
// 	}
// }

// void	check_dquote_index_at_data_index(t_expand_info *info)
// {
// 	info->dquote_i = resolve_quote_index_at_data_index(info->i, info->dquote_i);
// 	if (info->quote_i != -1)
// 	{
// 		info->expanded_data[info->j] = info->old_data[info->i];
// 		info->j++;
// 	}
// }
