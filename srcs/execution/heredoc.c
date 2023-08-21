/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 14:59:07 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/18 14:30:40 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_heredoc(char *data)
{
	int		fd[2];
	int		templen;
	int		datalen;
	char	*temp;
	bool	expand;

	if (pipe(fd) == -1)
	{
		ft_throw_error(errno, "pipe in heredoc failed");
		return (false);
	}
	datalen = ft_strlen(data);
	if ((data[0] == '\'' && data[datalen - 1] == '\'') || \
			(data[0] == '"' && data[datalen - 1] == '"'))
	{
		puts("quotes found :)");
		expand = false;
	}
	else
		expand = true;
	while (1)
	{
		temp = readline(">");
		templen = ft_strlen(temp);
		if (!ft_strncmp(temp, data, (templen + 1)))
		{
			free(temp);
			break ;
		}
		// if (temp[0] == '$' && expand == true)
		// {
		// 	// call expand function that returns the string if found in env else stays the same
		// }
		write(fd[1], temp, templen);
        write(fd[1], "\n", 1);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_throw_error(errno, "dup2 in heredoc failed");
	close(fd[0]);
	close(fd[1]);
	return (true);
}
// expand only if the delimiter is not between quotes. cat << EOF or cat << ";" / cat << ';' work differently.
// ";" or ';' expansion doesn't happen. check conv with leon for quotes.
