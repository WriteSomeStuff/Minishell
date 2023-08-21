/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_test_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:26:19 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/01 14:26:20 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	token_arr_assert_data(t_token **token_arr, char *data[])
{
	int	i;

	i = 0;
	while (token_arr[i] != NULL)
	{
		if (!str_equals(token_arr[i]->data, data[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	token_arr_assert_type(t_token **token_arr, t_token_type types[])
{
	int	i;

	i = 0;
	while (token_arr[i] != NULL)
	{
		if (token_arr[i]->type != types[i])
			return (false);
		i++;
	}
	return (true);
}