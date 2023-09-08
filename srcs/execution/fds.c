/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fds.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 12:39:09 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/07 18:04:26 by cheyennesch   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fds(t_init *process)
{
	size_t	i;

	i = 0;
	while (i < (process->nr_of_cmds - 1))
	{
		if (close(process->pipes[i][0]) == -1 || \
			close(process->pipes[i][1]) == -1)
			ft_throw_error(process, errno);
		i++;
	}
}

bool	ft_infile(t_init *process, t_rdr *rdr)
{
	int32_t	temp;

	process->fdin = open(rdr->data, O_RDONLY);
	if (process->fdin == -1 || dup2(process->fdin, STDIN_FILENO) == -1 || \
		close(process->fdin) == -1)
	{
		temp = errno;
		ft_putstr_fd("BabyBash: ", STDERR_FILENO);
		process->errorcode = 1;
		errno = temp;
		return (perror(rdr->data), false);
	}
	return (true);
}

bool	ft_outfile(t_init *process, t_rdr *rdr)
{
	int32_t	temp;

	if (rdr->type == RDR_APPEND)
		process->fdout = open(rdr->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		process->fdout = open(rdr->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (process->fdout == -1 || dup2(process->fdout, STDOUT_FILENO) == -1 || \
		close(process->fdout) == -1)
	{
		temp = errno;
		ft_putstr_fd("BabyBash: ", STDERR_FILENO);
		process->errorcode = 1;
		errno = temp;
		return (perror(rdr->data), false);
	}
	return (true);
}

bool	ft_check_for_heredoc(t_scmd_list *scmd, t_init *process)
{
	t_rdr	*rdr;
	
	while (scmd)
	{
		if (scmd->type == RDR)
		{
			rdr = scmd->data;
			if (rdr->type == HERE_DOC)
			{
				if (dup2(process->oldin, STDIN_FILENO) == -1)
				{
					ft_throw_error(process, errno);
					return (false);
				}
				if (!ft_heredoc(process, rdr->data))
					return (false);
				process->heredoc = true;
			}
		}
		scmd = scmd->next;
	}
	return (true);
}

bool	ft_check_for_files(t_scmd_list *scmd, t_init *process)
{
	t_rdr	*rdr;

	if (!ft_check_for_heredoc(scmd, process))
		return (false);
	while (scmd)
	{
		if (scmd->type == RDR)
		{
			rdr = scmd->data;
			if (rdr->type == RDR_INPUT)
			{
				if (!ft_infile(process, rdr))
					return (false);
			}
			if (rdr->type == RDR_OUTPUT || rdr->type == RDR_APPEND)
				ft_outfile(process, rdr);
		}
		scmd = scmd->next;
	}
	return (true);
}
// bash checks all for existing, if not existing infile, error, dont check the rest.
// if all infiles exist, only read out of last one. if all outfiles are created or existing, only send to last one.