/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:26:36 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 18:26:42 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

char *check_absolute_or_relative_path(char *cmd)
{
    if (!cmd || !*cmd)
        return (NULL);
    if (cmd[0] == '/' || cmd[0] == '.') {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    return (NULL);
}

char **get_path_directories(void)
{
    char *path_env;
    char **dirs;

    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);
    path_env = ft_strdup(path_env);
    if (!path_env)
        return (NULL);
    dirs = split_path(path_env);
    free(path_env);
    return (dirs);
}

char *search_command_in_dirs(char **dirs, char *cmd)
{
    int i;
    char *full_path;

    i = 0;
    while (dirs[i]) {
        full_path = join_path(dirs[i], cmd);
        if (full_path) {
            if (access(full_path, X_OK) == 0) {
                ft_free_tab(dirs);
                return (full_path);
            }
            free(full_path);
        }
        i++;
    }
    return (NULL);
}

char *find_command_path(char *cmd)
{
    char **dirs;
    char *result;

    result = check_absolute_or_relative_path(cmd);
    if (result)
        return (result);
    dirs = get_path_directories();
    if (!dirs)
        return (NULL);
    result = search_command_in_dirs(dirs, cmd);
    if (!result)
        ft_free_tab(dirs);
    return (result);
}
