/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:02:27 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/28 00:03:55 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void increment_shell_level(void)
{
    char *shlvl;
    int new_shlvl;
    char new_shlvl_str[12];

    shlvl = getenv("SHLVL");
    new_shlvl = 1;
    if (shlvl != NULL)
        new_shlvl = atoi(shlvl) + 1;

    snprintf(new_shlvl_str, sizeof(new_shlvl_str), "%d", new_shlvl);
    setenv("SHLVL", new_shlvl_str, 1);
}
