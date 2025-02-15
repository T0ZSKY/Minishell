/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:34:34 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/15 21:04:19 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//include

# include "stdio.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "../../includes/libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

//stucure
typedef struct s_shell
{
	int		is_running;
	char	**tab;
	char	**envp;
	char	*cmd;
}	t_shell;

typedef struct s_pipe
{
	int		fd[2];
	int		hdoc;
	int		prev_pipe;
	pid_t	pid;
	pid_t	pids[1024];
	char	**envp;
}	t_pipe;

typedef struct s_echo_data
{
	char	**envp;
	char	*result;
	int		i;
	int		j;
}	t_echo_data;

//SEULE VARIABLE GLOBALE OBLIGATOIRE POUR SIGNAL ; pas besoin de full maj bebou
extern int	g_last_exit_status;

//declaration
void	ft_lexer(char *input, t_shell *shell);
void	ft_echo(char **tab, char **envp);
void	ft_cmd(char **tab, char **envp, t_shell *shell);
void	ft_free_tab(char **tab);
char	*find_command_path(char *cmd);
char	*join_path(char *dir, char *cmd);
char	*replace_pipes(char *cmd);
char	**split_path(char *path);
void	ft_cd(char **tab, t_shell *shell);
void	increment_shell_level(void);
void	exec_pipes(char **command, t_shell *shell);
void	exec_child(char *cmd, int prev_pipe, int fd[2], t_shell *shell);
int		is_complex(char *input);
void	ft_export(char **tab, t_shell *shell);
t_shell	*init_shell(char **envp);
void	print_clean_str(char *str, int has_next);
int		handle_n_flag(char **tab, int *j);
char	**ft_copy_env(char **envp, int count);
void	ft_sort_env(char **sorted_env, int count);
void	ft_pwd(char **tab);
void	ft_ascii(void);
void	ft_env(char **tab, t_shell *shell);
void	ft_exit(t_shell *shell);
void	ctrl_c_handler(int sig);
void	ft_unset(char **tab, t_shell *shell);
int		is_custom_cmd(char *s);
void	ft_custom_cmd(t_shell *shell);
char	**ft_splitfou(char *str);
int		ft_custom_cmd_args(char *cmd, t_shell *shell);
char	*redirections(char *cmd);
int		heredoc(char *limiter);
void	null_complex(char **redir);
void	ft_cmd_test(char *cmd, char **envp);
char	*handle_exit_status(int *index);
int		get_var_length(char *str, int i);
char	*get_var_name(char *str, int i, int len);
char	*find_env_value(char *var_name, int len, char **envp);
void	init_signals(void);
int		process_redirection(char **cmd);
char	*format_redirection_string(char *cmd, char *new_cmd);
void	ft_handle_pipes(char *input, t_shell *shell);
void	ft_execute_command(t_shell *shell, char *input);
int		calculate_new_length(char *cmd);
void	copy_with_spaces(char *dest, const char *src);
int		handle_redirection(char *redir_type, char *file, int mode);
int		process_redirections(char **command, int *i);
int		process_heredoc_redirection(char **command, int *i);
int		process_output_redirection(char **command, int *i);
int		process_input_redirection(char **command, int *i);
int		process_append_redirection(char **command, int *i);

#endif
