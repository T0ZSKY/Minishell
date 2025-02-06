/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:49:51 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/06 17:31:21 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

void ft_cd(char **tab, t_shell *shell)
{
    int i;
    int path_found;
    char *home_path = NULL;

    i = 0;
    path_found = 0;
    while (shell->envp[i]) 
    {
        if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0) 
        {
            path_found = 1;
            break;
        }
        i++;
    }

    if (!path_found) 
    {
        printf("minishell: cd: No such file or directory\n");
        g_last_exit_status = 127;
        return;
    }
    i = 0;
    while (shell->envp[i]) 
    {
        if (ft_strncmp(shell->envp[i], "HOME=", 5) == 0) 
        {
            home_path = shell->envp[i] + 5;
            break;
        }
        i++;
    }

    if (!tab[1])
    {
        if (home_path && chdir(home_path) == 0)
            g_last_exit_status = 0;
        else
        {
            g_last_exit_status = 1;
            printf("cd: cannot change directory to HOME\n");
        }
        return;
    }
    if (chdir(tab[1]) == 0)
        g_last_exit_status = 0;
    else
    {
        g_last_exit_status = 1;
        printf("cd: %s: No such file or directory\n", tab[1]);
    }
}

