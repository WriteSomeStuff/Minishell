/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 13:32:13 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/10 16:43:33 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// one builtin doesnt create child processes, but does when pipes are used. 
// needs to be able to write into pipe too, also handle $?
void	ft_echo_builtin(t_cmd *info)
{
	int	i;

	i = 1;
	if (!info->arg[i] || !info->arg[i][0])
	{
		printf("\n");
		return ;
	}
	if (info->arg[i] && str_equals("-n", info->arg[1]))
	{
		while (str_equals("-n", info->arg[i]))
		{
			i++;
			if (!info->arg[i])
				return ;
		}
		while (info->arg[i + 1])
			printf("%s ", info->arg[i++]);
		printf("%s", info->arg[i++]);
		return ;
	}
	while (info->arg[i + 1])
		printf("%s ", info->arg[i++]);
	printf("%s\n", info->arg[i]);
}

// only changes directory inside the process, which exits.
// I can print current dir with getcwd to test if it actually changed.
void	ft_cd_builtin(t_cmd *info)
{
	if (chdir(info->arg[1]) == -1)
		ft_throw_error(errno, "chdir failed");
}

void	ft_pwd_builtin(void)
{
	char	buffer[MAXPATHLEN];

	if (getcwd(buffer, MAXPATHLEN) == NULL)
		ft_throw_error(errno, "pwd failed");
	printf("%s\n", buffer);
}

// I made it so it always exits with an int between 0-255 just like bash does.
void	ft_exit_builtin(t_cmd *info)
{
	int				i;
	long long int	string_to_llong;

	i = 0;
	if (!info->arg[1])
		exit(0);
	if (info->arg[1][0] == '-' || info->arg[1][0] == '+')
		i++;
	while (info->arg[1][i])
	{
		if (!ft_isdigit(info->arg[1][i]))
			ft_throw_error(255, "numeric argument required");
		i++;
	}
	string_to_llong = ft_atollong(info->arg[1]) % 256;
	if (string_to_llong < 0)
		string_to_llong += 256;
	printf("%s\n", "exit");
	exit(string_to_llong);
}
