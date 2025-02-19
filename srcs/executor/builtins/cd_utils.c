/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 22:45:44 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/19 22:46:38 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

char	*get_current_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	return (pwd);
}

int	find_env_var(char **envp, const char *var_name)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, var_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;
	int		pwd_index;
	int		oldpwd_index;
	char	*new_pwd_str;
	char	*new_oldpwd_str;

	new_pwd = get_current_pwd();
	if (!new_pwd || !old_pwd)
		return ;
	pwd_index = find_env_var(shell->envp, "PWD=");
	oldpwd_index = find_env_var(shell->envp, "OLDPWD=");
	new_pwd_str = ft_strjoin("PWD=", new_pwd);
	new_oldpwd_str = ft_strjoin("OLDPWD=", old_pwd);
	if (pwd_index >= 0 && new_pwd_str)
	{
		free(shell->envp[pwd_index]);
		shell->envp[pwd_index] = new_pwd_str;
	}
	if (oldpwd_index >= 0 && new_oldpwd_str)
	{
		free(shell->envp[oldpwd_index]);
		shell->envp[oldpwd_index] = new_oldpwd_str;
	}
	free(new_pwd);
}
