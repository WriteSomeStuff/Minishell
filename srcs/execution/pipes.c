/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 13:32:13 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/10 14:31:26 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		pipes[i] = NULL;
		i++;
	}
	if (pipes)
	{
		free(pipes);
		pipes = NULL;
	}
}

int	ft_count_pipes(t_list *lst)
{
	int		pipe_count;

	pipe_count = 0;
	while (lst->next)
	{
		pipe_count++;
		lst = lst->next;
	}
	return (pipe_count);
}

int	**ft_create_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	pipes = malloc(pipe_count * sizeof(int *));
	if (!pipes)
		return (perror("minishell: "), NULL);
	while (i < pipe_count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("minishell: ");
			ft_free_pipes(pipes, pipe_count);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
