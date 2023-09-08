// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   parsertest.c                                       :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/08/24 16:48:04 by mstegema      #+#    #+#                 */
// /*   Updated: 2023/08/29 15:08:32 by mstegema      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// static void	print_commandlist(t_list *lst)
// {
// 	t_scmd_list	*scmd;
// 	t_cmd		*cmd;
// 	t_rdr		*rdr;
// 	int			i;
// 	int			j;

// 	i = 1;
// 	while (lst != NULL)
// 	{
// 		printf("______________________________________________________________________\n");
// 		printf("scmd #%i\n", i);
// 		scmd = lst->content;
// 		while (scmd != NULL)
// 		{
// 			printf("node type:	[%d]\n", scmd->type);
// 			if (scmd->type == CMD)
// 			{
// 				cmd = scmd->data;
// 				printf("path:		%s\n", cmd->path);
// 				j = 0;
// 				while (cmd->arg[j] != NULL)
// 				{
// 					printf("args:		%s\n", cmd->arg[j]);
// 					j++;
// 				}
// 				printf("builtin:	%d\n\n", cmd->builtin);
// 			}
// 			else if (scmd->type == RDR)
// 			{
// 				rdr = scmd->data;
// 				printf("data:		%s\n", rdr->data);
// 				printf("rdr type:	%d\n\n", rdr->type);
// 			}
// 			scmd = scmd->next;
// 		}
// 		lst = lst->next;
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	char	*user_input;
// 	t_list	*cmds;

// 	user_input = "cat << \";\" | grep \"aap noot mies\" | wc -l > outfile | >l";
// 	// user_input = "cat";
// 	// printf("user input: %s\n______________________________________________________________________\n", user_input);
// 	cmds = parse(NULL, user_input);
// 	print_commandlist(cmds);
// 	return (0);
// }
