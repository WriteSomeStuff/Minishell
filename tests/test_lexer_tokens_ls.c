/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_lexer_tokens_ls.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:26:37 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/10 16:53:04 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parameters in format: {command_line},{expected_types},{expected_data},{expected_length}
// static char *ls_params[] = {
// 	(char *) "ls,1,ls,1",
// 	(char *) "ls -l,1 2,ls -l,2",
// 	(char *) "ls -l | grep,1 2 4 1,ls -l | grep,4",
// 	(char *) "ls -l | grep \"Makefile\",1 2 4 1 2,ls -l | grep \"Makefile\",5",
// 	(char *) "cat < infile | grep \"text\" > outfile,1 3 1 4 1 2 3 1,cat < infile | grep \"text\" > outfile,8",
// 	(char *) "cat < infile | grep \"text\" >> outfile,1 3 1 4 1 2 3 1,cat < infile | grep \"text\" >> outfile,8",
// 	(char *) "cat << \";\" | grep \"text\" > outfile,1 3 1 4 1 2 3 1,cat << \";\" | grep \"text\" > outfile,8",
// 	(char *) "cat << \";\" | grep \"text\" >> outfile,1 3 1 4 1 2 3 1,cat << \";\" | grep \"text\" >> outfile,8", 
// 	NULL
// };
