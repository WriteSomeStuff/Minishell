/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_ppid.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:43:46 by mstegema      #+#    #+#                 */
/*   Updated: 2023/12/12 15:02:32 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_ppid(void)
{
	char	*temp;
	char	*ppid_str;
	int		proc_fd;

	temp = ft_calloc(1, sizeof(char));
	ppid_str = NULL;
	proc_fd = open("/proc/self/status", O_RDONLY);
	if (proc_fd < 0)
		return (ft_free_str_array(NULL, temp), NULL);
	while (temp != NULL)
	{
		if (ft_strnstr(temp, "PPid", 4) != NULL)
		{
			ppid_str = ft_strjoin("", temp + 6);
			if (!ppid_str)
				return (close(proc_fd), ft_free_str_array(NULL, temp), NULL);
			ppid_str[7] = '\0';
			return (close(proc_fd), ft_free_str_array(NULL, temp), ppid_str);
		}
		ft_free_str_array(NULL, temp);
		temp = get_next_line(proc_fd);
		if (!temp)
			return (NULL);
	}
	return (close(proc_fd), ft_free_str_array(NULL, temp), ppid_str);
}
