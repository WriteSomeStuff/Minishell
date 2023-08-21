/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_array_utilities.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:25:47 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/01 14:25:49 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_arr_length(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
		i++;
	return (i);
}
