// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   lexertest.c                                        :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/08/24 15:09:45 by mstegema      #+#    #+#                 */
// /*   Updated: 2023/08/31 15:36:07 by mstegema      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// static void	print_array(char **array)
// {
// 	while (array[0] != '\0')
// 	{
// 		printf("array str: [%s]\n", *array);
// 		array++;
// 	}
// }

// static void	print_tlist(t_list *list)
// {
// 	t_token	*current;

// 	current = list->content;
// 	while (list != NULL && list->next != NULL)
// 	{
// 		printf("data: [%s]	type: [%d]\n", current->data, current->type);
// 		list = list->next;
// 		current = list->content;
// 	}
// 	if (list != NULL)
// 		printf("data: [%s]	type: [%d]\n", current->data, current->type);
// }

// t_token	*is_splitable(t_token *token)
// {
// 	char	*data;
// 	char	*new_data;
// 	size_t	len;
// 	t_token	*new;

// 	data = token->data;
// 	new_data = NULL;
// 	len = ft_strlen(data);
// 	new = NULL;
// 	if (len > 2 && ft_strchr("<>", data[0]) && ft_strchr("<>", data[1]) \
// 	&& ft_strchr("<>", data[2]) == NULL)
// 		new_data = ft_substr(data, 2, len);
// 	else if (len > 1 && ft_strchr("<>", data[0]) \
// 	&& ft_strchr("<>", data[1]) == NULL)
// 		new_data = ft_substr(data, 1, len);
// 	if (new_data)
// 		new = new_token(new_data, CMD_TOKEN);
// 	return (new);
// }

// static size_t	split_rdrtokens(t_list *tokens)
// {
// 	t_token	*token;
// 	t_list	*next;
// 	t_token	*new;
// 	t_list	*new_node;

// 	while (tokens != NULL)
// 	{
// 		token = tokens->content;
// 		next = tokens->next;
// 		new = NULL;
// 		if (token->type == RDR_TOKEN)
// 			new = is_splitable(token);
// 		if (new)
// 		{
// 			new_node = ft_lstnew(new);
// 			tokens->next = new_node;
// 			new_node->next = next;
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }

// static size_t	merge_tokens(t_list *tokens)
// {
// 	t_list	*begin;
// 	t_list	*end;
// 	t_token	*token;
// 	t_token	*next_token;

// 	while (tokens != NULL)
// 	{
// 		begin = quote_begin(tokens);
// 		end = quote_end(begin);
// 		if (begin == NULL || end == NULL)
// 			return (1); //no quotes || no ending quotes
// 		token = begin->content;
// 		tokens = begin;
// 		while (tokens != end)
// 		{
// 			next_token = tokens->next->content;
// 			token->data = ft_strjoin(token->data, " ");
// 			token->data = ft_strjoin(token->data, next_token->data);
// 			tokens = tokens->next;
// 		}
// 		begin->next = end->next;
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }

// static t_token	*init_token(const char *str)
// {
// 	if (ft_strncmp(str, "|", 2) == 0)
// 		return (new_token(str, PIPE_TOKEN));
// 	else if ((ft_strncmp(str, ">", 1) == 0) || (ft_strncmp(str, "<", 1) == 0)
// 		|| (ft_strncmp(str, ">>", 2) == 0) || (ft_strncmp(str, "<<", 2) == 0))
// 		return (new_token(str, RDR_TOKEN));
// 	else
// 		return (new_token(str, CMD_TOKEN));
// }

// static size_t	make_tlist(const char **ui_array, t_list **tokens)
// {
// 	t_list	*node;
// 	t_token	*token;
// 	char	*str;

// 	while (ui_array[0] != '\0')
// 	{
// 		str = (char *)*ui_array;
// 		token = init_token(str);
// 		if (token == NULL)
// 			return (ft_lstclear(tokens, &free), 1);
// 		node = ft_lstnew(token);
// 		if (node == NULL)
// 			return (ft_lstclear(tokens, &free), 1);
// 		ft_lstadd_back(tokens, node);
// 		ui_array++;
// 	}
// 	return (0);
// }

// t_list	*tokenisation(const char *user_input)
// {
// 	t_list	*tokens;
// 	char	**ui_array;

// 	tokens = NULL;
// 	ui_array = ft_split(user_input, ' ');
// 	if (!ui_array)
// 		exit(1); //exit "failed to parse"?
// 	print_array(ui_array);
// 	make_tlist((const char **) ui_array, &tokens);
// 	printf("\nafter make	(CMD_OR_FILE = 1, REDIRECTION = 2, PIPE = 3)\n");
// 	printf("______________________________________________________________________\n");
// 	print_tlist(tokens);

// 	merge_tokens(tokens);
// 	printf("\nafter merge	(CMD_OR_FILE = 1, REDIRECTION = 2, PIPE = 3)\n");
// 	printf("______________________________________________________________________\n");
// 	print_tlist(tokens);

// 	split_rdrtokens(tokens);
// 	printf("\nafter split	(CMD_OR_FILE = 1, REDIRECTION = 2, PIPE = 3)\n");
// 	printf("______________________________________________________________________\n");
// 	print_tlist(tokens);
// 	return (tokens);
// }

// int	main(void)
// {
// 	char	*user_input;
// 	t_list	*tokens;

// 	tokens = NULL;
// 	user_input = "cat <<potato \";\" | grep \"aap noot mies\" | wc -l > outfile | >l";
// 	// user_input = "cat << \";\" | grep \"aap | wc -l > outfile | >l";
// 	printf("user input: %s\n______________________________________________________________________\n", user_input);
// 	tokens = tokenisation(user_input);
// 	return (0);
// }










