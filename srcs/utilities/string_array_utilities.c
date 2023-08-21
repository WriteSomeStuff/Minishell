/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_array_utilities.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:25:35 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/01 14:25:37 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_array_length(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i] != NULL)
		i++;
	return (i);
}

void	str_array_free(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i] != NULL)
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}
