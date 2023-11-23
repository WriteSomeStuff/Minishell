/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 13:32:13 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/08 17:12:08 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipes(t_init *process, int32_t pipe_count)
{
	int32_t	i;

	i = 0;
	while (i < pipe_count)
	{
		free(process->pipes[i]);
		process->pipes[i] = NULL;
		i++;
	}
	process->pipe_count = 0;
	if (process->pipes)
	{
		free(process->pipes);
		process->pipes = NULL;
	}
}

int32_t	ft_count_pipes(t_list *lst)
{
	int32_t	pipe_count;

	pipe_count = 0;
	while (lst->next)
	{
		pipe_count++;
		lst = lst->next;
	}
	return (pipe_count);
}

bool	ft_create_pipes(t_init *process, size_t pipe_count)
{
	size_t	i;

	i = 0;
	process->pipes = malloc(pipe_count * sizeof(int32_t *));
	if (!process->pipes)
		return (perror("BabyBash"), false);
	while (i < pipe_count)
	{
		process->pipes[i] = malloc(2 * sizeof(int32_t));
		if (!process->pipes[i] || pipe(process->pipes[i]) == -1)
		{
			perror("BabyBash");
			ft_free_pipes(process, i);
			return (false);
		}
		i++;
	}
	return (true);
}
