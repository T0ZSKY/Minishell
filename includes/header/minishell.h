/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:34:34 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 18:45:49 by taomalbe         ###   ########.fr       */
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

# include "stdio.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "../../includes/libft/libft.h"


//declaration
void	ft_lexer(char *input, t_shell *shell);
void	ft_echo(char **tab);
int		is_complex(char *input);

#endif
