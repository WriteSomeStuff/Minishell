/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   childprocess.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 13:32:13 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/08 12:40:36 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_for_last_child(t_init *process)
{
	ft_close_fds(process);
	waitpid(process->ids[process->nr_of_cmds - 1], &process->status, 0);
	if (WIFEXITED(process->status))
		process->errorcode = WEXITSTATUS(process->status);
	else if (WIFSIGNALED(process->status))
	{
		process->errorcode = 128 + WTERMSIG(process->status);
		printf("after wait: %i\n", process->errorcode); // remove
	}
	while (1)
	{
		if (wait(NULL) == -1)
			break ;
	}
	free(process->ids);
	process->ids = NULL;
}

static void	ft_child_process(t_list *lst, t_init *process)
{
	if (!process->fdout && ((!process->i && process->nr_of_cmds > 1) || \
		(process->i != (process->nr_of_cmds - 1))))
	{
		if (dup2(process->pipes[process->i][1], STDOUT_FILENO) == -1)
		{
			ft_throw_error(process, errno);
			exit(process->errorcode);
		}
	}
	if (process->i != 0 && process->heredoc == false && !process->fdin)
	{
		if (dup2(process->pipes[process->i - 1][0], STDIN_FILENO) == -1)
		{
			ft_throw_error(process, errno);
			exit(process->errorcode);
		}
	}
	ft_close_fds(process);
	if (process->cmd->builtin == false)
		ft_execve(process->cmd);
	else
	{
		ft_run_builtin(lst, process, process->cmd);
		exit(process->errorcode);
	}
}

static void	ft_find_cmd(t_scmd_list *lst, t_init *process)
{
	while (lst)
	{
		if (lst->type == CMD)
		{
			process->cmd = lst->data;
			break ;
		}
		lst = lst->next;
	}
	if (!lst)
		process->cmd = NULL;
}

void	ft_create_child(t_list *lst, t_init *process)
{
	ft_find_cmd(lst->content, process);
	if (process->cmd)
	{
		process->ids[process->i] = fork();
		if (process->ids[process->i] == -1)
		{
			ft_throw_error(process, errno);
			return ;
		}
		if (process->ids[process->i] == 0)
			ft_child_process(lst, process);
		process->i++;
	}
	process->heredoc = false;
	process->fdout = 0;
	process->fdin = 0;
}
