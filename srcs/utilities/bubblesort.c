/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bubblesort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 12:07:08 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/14 13:36:52 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_bubble_sort(char **sortedenv, int32_t len)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	while (i < len - 1)
	{
		while (j < len - i - 1)
		{
			if (ft_strncmp(sortedenv[j], sortedenv[j + 1], MAXPATHLEN) > 0)
				ft_swap(&sortedenv[j], &sortedenv[j + 1]);
			j++;
		}
		j = 0;
		i++;
	}
}
