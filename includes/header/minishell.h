/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:34:34 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/28 00:04:04 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

//stucure
typedef struct s_shell
{
	int is_running;
	char **tab;
} t_shell;

//include

#include "stdio.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "../../includes/libft/libft.h"
#include <unistd.h>


//declaration
void ft_lexer(char *input, t_shell *shell, char **envp);
void ft_echo(char **tab);
void ft_cmd(char **tab, char **envp);
void ft_free_tab(char **tab);
char *find_command_path(char *cmd);
char *join_path(char *dir, char *cmd);
char **split_path(char *path);
void ft_cd(char **tab);
void increment_shell_level(void);


#endif
