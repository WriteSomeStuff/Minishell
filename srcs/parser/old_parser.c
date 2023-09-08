// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   old_parser.c                                       :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/08/01 14:24:50 by cschabra      #+#    #+#                 */
// /*   Updated: 2023/08/24 17:09:07 by mstegema      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	free_command(t_cmd *command)
// {
// 	free(command);
// }

// t_cmd	*alloc_command(t_list *tokens, t_env *environment)
// {
// 	t_cmd	*command;

// 	if (ft_lstsize(tokens) == 0)
// 		return (NULL);
// 	command = (t_cmd *)malloc(sizeof(t_cmd));
// 	if (command == NULL)
// 		return (NULL);
// 	command->env = environment;
// 	return (command);
// }

// bool	add_command_node(t_list *cmd_tokens, t_list **commands, t_env *environment)
// {
// 	t_cmd	*command;
// 	t_list	*command_item;

// 	command = alloc_command(cmd_tokens, environment);
// 	if (command == NULL)
// 		return (false);
// 	command_item = ft_lstnew(command);
// 	if (command_item == NULL)
// 		return (free_command(command), false);
// 	ft_lstadd_back(commands, command_item);
// 	return (true);
// }

// bool	parse_tokens(t_list *tokens, t_list *commands, t_env *environment)
// {
// 	t_list	*current;
// 	t_list	*cmd_tokens;
// 	t_list	*cmd_token;
// 	t_token	*token;

// 	cmd_tokens = NULL;
// 	current = tokens;
// 	while (current != NULL)
// 	{
// 		token = (t_token *)current->content;
// 		if (token->type == PIPE_TOKEN)
// 		{
// 			if (!add_command_node(cmd_tokens, &commands, environment))
// 				return (lst_free(&cmd_tokens), false);
// 			lst_free(&cmd_tokens);
// 		}
// 		else
// 		{
// 			cmd_token = ft_lstnew(token);
// 			if (cmd_token == NULL)
// 				return (lst_free(&cmd_tokens), false);
// 			ft_lstadd_back(&cmd_tokens, cmd_token);
// 		}
// 		current = current->next;
// 	}
// 	if (ft_lstsize(cmd_tokens) != 0)
// 	{
// 		ft_put_token_lst(cmd_tokens);
// 		if (!add_command_node(cmd_tokens, &commands, environment))
// 			return (lst_free(&cmd_tokens), false);
// 		lst_free(&cmd_tokens);
// 	}
// 	return (true);
// }

// // int	main(int argc, char *argv[], char *env[])
// // {
// // 	(void)argc;
// // 	(void)argv;
// // 	t_env	*environment;
// // 	t_list	*tokens;
// // 	t_list	*cmds;

// // 	environment = (t_env *)malloc(sizeof(t_env));
// // 	if (environment == NULL)
// // 		return (EXIT_FAILURE);
// // 	ft_copy_env(environment, env);
// // 	tokens = read_tokens_from_command_line("echo \"hallo $USER\" | cat hallo");
// // 	if (tokens == NULL)
// // 		exit(EXIT_FAILURE);
// // 	if (!expand_tokens(tokens))
// // 		return (EXIT_FAILURE);
// // 	cmds = NULL;
// // 	if (!parse_tokens(tokens, cmds, environment))
// // 		exit(EXIT_FAILURE);
// // 	ft_put_token_lst(tokens);
// // 	ft_lstclear(&tokens, &token_free);
// // 	free_env(environment);
// // 	//system("leaks -q minishell");
// // 	return (EXIT_SUCCESS);
// // }
