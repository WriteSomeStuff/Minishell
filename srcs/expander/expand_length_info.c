/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_length_info.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:23:48 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/01 14:23:51 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expand_length_data_at(t_expand_length_info info, char c)
{
	return (info.data[info.i] == c);
}

void	init_expand_length_info(t_expand_length_info *info, char *data)
{
	info->i = 0;
	info->length = 0;
	info->quote_i = -1;
	info->dquote_i = -1;
	info->data = data;
}

void	update_quote(t_expand_length_info *info)
{
	info->quote_i = resolve_quote_index_at_data_index(info->i, info->quote_i);
	if (info->dquote_i != -1)
		info->length++;
}

void	update_dquote(t_expand_length_info *info)
{
	info->dquote_i = resolve_quote_index_at_data_index(info->i, info->dquote_i);
	if (info->quote_i != -1)
		info->length++;
}
