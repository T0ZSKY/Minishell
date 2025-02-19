/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:49:51 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/19 22:45:20 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

static int	check_path_exists(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	printf("minishell: cd: No such file or directory\n");
	g_last_exit_status = 127;
	return (0);
}

static char	*get_home_path(char **envp)
{
	int		i;
	char	*home_path;

	i = 0;
	home_path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			home_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (home_path);
}

static void	handle_home_dir(char *home_path)
{
	if (home_path && chdir(home_path) == 0)
		g_last_exit_status = 0;
	else
	{
		g_last_exit_status = 1;
		printf("cd: cannot change directory to HOME\n");
	}
}

static void	change_directory(char *path)
{
	if (chdir(path) == 0)
		g_last_exit_status = 0;
	else
	{
		g_last_exit_status = 1;
		printf("cd: %s: No such file or directory\n", path);
	}
}

void	ft_cd(char **tab, t_shell *shell)
{
	char	*home_path;
	char	*old_pwd;

	if (!check_path_exists(shell->envp))
		return ;
	old_pwd = get_current_pwd();
	if (!old_pwd)
	{
		printf("cd: error getting current directory\n");
		g_last_exit_status = 1;
		return ;
	}
	home_path = get_home_path(shell->envp);
	if (!tab[1])
		handle_home_dir(home_path);
	else
		change_directory(tab[1]);
	update_pwd_vars(shell, old_pwd);
	free(old_pwd);
}
