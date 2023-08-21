/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 17:02:44 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/18 15:30:30 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test example: ./minishell_test infile "cat /dev/urandom" "head -n 5" cat cat outfile
// copy env, make history? make tokens, expand tokens, parse, execute, repeat?
// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	env;
// 	// t_list	*tokens;
// 	// t_list	*cmds;

// 	argc = 0;
// 	ft_copy_env(&env, envp);
// 	ft_test_child(&env, argv);
// 	// tokens = read_tokens_from_command_line("echo \"hallo $USER\" | cat hallo");
// 	// if (tokens == NULL)
// 	// 	exit(EXIT_FAILURE);
// 	// if (!expand_tokens(tokens))
// 	// 	return (EXIT_FAILURE);
// 	// cmds = NULL;
// 	// if (!parse_tokens(tokens, cmds, env))
// 	// 	exit(EXIT_FAILURE);
// 	// ft_put_token_lst(tokens);
// 	// ft_lstclear(&tokens, &token_free);
// 	ft_free_env(env.new_env, NULL);
// 	// system("leaks -q minishell_test");
// 	return (EXIT_SUCCESS);
// }
