/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:34:34 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/20 14:58:10 by taomalbe         ###   ########.fr       */
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

int		is_quote(char c);
int		is_whitespace(char c);
int		is_custom_cmd(char *s);
int		heredoc(char *limiter);
int		is_complex(char *input);
int		ft_count_word(char *input);
int		has_unclosed_quotes(char *str);
int		calculate_new_length(char *cmd);
int		process_redirection(char **cmd);
int		get_var_length(char *str, int i);
int		handle_n_flag(char **tab, int *j);
int		skip_quotes(char *str, int i, char quote);
int		process_redirections(char **command, int *i);
int		ft_custom_cmd_args(char *cmd, t_shell *shell);
int		find_env_var(char **envp, const char *var_name);
int		process_input_redirection(char **command, int *i);
int		process_append_redirection(char **command, int *i);
int		process_output_redirection(char **command, int *i);
int		process_heredoc_redirection(char **command, int *i);
int		handle_redirection(char *redir_type, char *file, int mode);

void	ft_ascii(void);
void	ft_pwd(char **tab);
void	init_signals(void);
void	free_envp(char **envp);
void	ft_exit(t_shell *shell);
void	ft_free_tab(char **tab);
void	ctrl_c_handler(int sig);
void	null_complex(char **redir);
void	increment_shell_level(void);
void	ft_custom_cmd(t_shell *shell);
void	ft_echo(char **tab, char **envp);
void	ft_cd(char **tab, t_shell *shell);
void	ft_env(char **tab, t_shell *shell);
void	ft_cmd_test(char *cmd, char **envp);
void	ft_unset(char **tab, t_shell *shell);
void	ft_export(char **tab, t_shell *shell);
void	ft_lexer(char *input, t_shell *shell);
void	print_clean_str(char *str, int has_next);
void	ft_sort_env(char **sorted_env, int count);
void	exec_pipes(char **command, t_shell *shell);
void	ft_handle_pipes(char *input, t_shell *shell);
void	copy_with_spaces(char *dest, const char *src);
void	update_pwd_vars(t_shell *shell, char *old_pwd);
void	ft_cmd(char **tab, char **envp, t_shell *shell);
void	ft_execute_command(t_shell *shell, char *input);
void	add_token(char **tokens, char *token, int *count);
void	exec_child(char *cmd, int prev_pipe, int fd[2], t_shell *shell);

char	*get_current_pwd(void);
char	*redirections(char *cmd);
char	*replace_pipes(char *cmd);
char	*remove_quotes(char *str);
char	*find_command_path(char *cmd);
char	*handle_exit_status(int *index);
char	*join_path(char *dir, char *cmd);
char	*add_spaces_redirections(char *cmd);
char	*get_var_name(char *str, int i, int len);
char	*format_redirection_string(char *cmd, char *new_cmd);
char	*find_env_value(char *var_name, int len, char **envp);
char	*get_cleaned_token(char *input, int start, int end, int preserve);

char	**split_path(char *path);
char	**ft_splitfou(char *str);
char	**ft_copy_env(char **envp, int count);
char	**ft_split_quotes(char *input, int preserve_quotes);

t_shell	*init_shell(char **envp);

#endif
