/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 17:02:44 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/24 17:44:59 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	g_signal = 0;

static t_string_status	read_from_line(char **str)
{
	*str = readline("BabyBash$ ");
	if (!*str)
	{
		ft_putendl_fd("Exit", STDERR_FILENO);
		return (NO_STRING);
	}
	else if (!*str[0])
	{
		ft_free_str_array(NULL, *str);
		return (EMPTY_STRING);
	}
	else
		return (VALID_STRING);
}

static void	ft_loop(t_list *lst, t_init *process)
{
	char			*str;
	t_string_status	readline_return;

	str = NULL;
	while (1)
	{
		if (!ft_setup_interactive(process))
			break ;
		readline_return = read_from_line(&str);
		if (readline_return == NO_STRING)
			break ;
		else if (readline_return == EMPTY_STRING)
			continue ;
		str = complete_input(process, str);
		if (!str || !ft_setup_noninteractive(process))
			break ;
		if (ft_strlen(str))
			add_history(str);
		lst = parse(process->env, process, str);
		ft_free_str_array(NULL, str);
		if (process->must_exit == true || !ft_executor(lst, process))
			break ;
	}
	rl_clear_history();
}


int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_list	lst;
	t_init	process;
	t_env	env;

	(void)argv, (void)argc;
	process.errorcode = 0;
	process.must_exit = false;
	if (!ft_copy_env(&process, &env, envp))
		return (process.errorcode);
	process.env = &env;
	ft_loop(&lst, &process);
	if (g_signal == SIGINT)
		process.errorcode = 130;
	ft_free_str_array(env.new_env, NULL);
	return (process.errorcode);
}
