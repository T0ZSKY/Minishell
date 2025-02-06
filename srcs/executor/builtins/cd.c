/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:49:51 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/05 15:54:09 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

void ft_cd(char **tab)
{
    if (!tab[1])
    {
        if (chdir(getenv("HOME")) == 0)
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
