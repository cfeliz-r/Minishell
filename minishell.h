#ifndef MINISHELL_H
# define MINISHELL_H
#define DARK_GRAY   "\x1b[90m"
#define BLUE        "\x1b[34m"
#define LIGHT_GRAY   "\x1b[37m"
#define CYAN        "\x1b[36m"
#define ORANGE "\033[38;5;208m"
#define DARK_FOREST "\033[38;5;22m"
#define FOREST_GREEN "\033[38;5;28m"
#define LUSH_GREEN "\033[38;5;34m"
#define BRIGHT_JUNGLE "\033[38;5;46m"
#define JUNGLE_GREEN "\033[38;5;34m"
#define RESET "\033[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "structs.h"
#include <errno.h>
#include "libft/libft.h"
#include <signal.h>

char *safe_strjoin_free(char *s1, const char *s2);
char	*split_quotes(char *str);
int		ft_count(char **split_result);
void	initialize_output_redirection(char **output_redirection,
	t_command *command);
void	store_output_redirections(char **split_result,
		t_command *command, int count);
int	count_output_redirections(char **split_result);
void	setup_signal_handler(struct sigaction *sa_int);
void	fork_and_process(t_command *commands, int i, int num_cmds, char **env_array, t_list_env *envp, int **pipes, struct sigaction *sa_int);
void	setup_pipes(int **pipes, int num_cmds);
void	remove_quotes_from_args(char **args);
char	*remove_quotes(char *str);
int	is_builtin_command(char *cmd);
void	child_process(t_command *command, int i, int num_cmds, char **env_array, t_list_env *envp, int **pipes);
void	execute_command(t_command *command, char **env_array, t_list_env *envp);
void	set_signal_handlers(void);
int	is_builtin_command(char *cmd);
char	*remove_quotes(char *str);
void	remove_quotes_from_args(char **args);
void	setup_pipes(int **pipes, int num_cmds);
char	*join_paths(char *dir, char *cmd);
char	**get_paths(t_list_env *envp);
char	*search_paths(char **paths, char *cmd);
char	*handle_command_path(char *clean_cmd, t_list_env *envp);
int	is_command_path_valid(char *clean_cmd);
int     is_space(int c);
void	handle_n_option(char **str, int *n_option);
void	print_parts(char **str, int start_index, int *first_part);
char	*strip_quotes(char *str);
char	**split_special(const char *input);
void	split_and_add_commands(const char *input, t_split_context *ctx);
void	init_vars(t_split_context *ctx);
void	add_command(t_split_context *ctx);
int	is_separator(const char *input, t_split_context *ctx);
void	handle_quotes_and_spaces(const char *input, t_split_context *ctx);
void	init_memory(const char *input, t_split_context *ctx);
int	is_n_option(char *str);
void	clean_up_echo(char **arr);
int	handle_quotes_3(char **start);
void	siginit(void);
void	process_input(t_list_env *envp);
int	all_is_space(char *start, char *end);
int	has_space(char *start, char *end);
int	validate_arguments(char *line);
void	exit_with_error(const char *message);
char	*remove_spaces(const char *str);
int	check_syntax(char *line);
int	check_redirections(char *line);
int	check_special_chars(char *line);
int	check_quotes(char *command);
int	contains_quotes(const char *str);
int	handle_initial_checks(char *line, char **aux);
int	check_quotes_and_special_chars(char *line);
int	check_redirections_and_syntax(char *line);
int	handle_syntax_checks(char *line);
int contains_quotes(const char *str);
int is_builtin_command(char *cmd);
void        remove_quotes_from_args(char **args);
void        prepare_commands(t_command *commands, int num_cmds, t_list_env *envp);
int         ft_parsing(char *line);
void        process_redirections(t_command *command);
int         handle_export(t_command *comand, t_list_env *environ);
void        siginit(void);
int         process_here_doc(t_command *command);
void        sigint_handler_ha(int sig);
int	        handle_cd(t_command *comand);
int	        handle_echo(t_command *comand);
int	        handle_env(t_command *comand, t_list_env *environ);
int         handle_pwd(t_command *comand);
size_t      aux_count(char **array);
int         all_digits(const char *str);
void        setup_signals(void);
int         count_envp(t_list_env *envp);
char        **convert_envp_to_array(t_list_env *envp);
t_command   *init_commands(char **command_strings, int num_cmds);
char        *ft_redir_cmd(char *input, t_list_env *envp);
int         validate_command(t_command *command, t_list_env *envp);
int         manage_error(int error_code, int return_value);
void handle_key_redir(t_command *command);
void        execute_commands(t_list_env *list, char *cmd);
//lists
t_list_env  *create_list_envp(char **envp);
void        clean_up_aux(t_command **commands);
void        free_command(t_command *command);
int         handle_redirections(t_command *command);
//signals
void        sigint_handler_2(int sig);
void        sigint_handler(int sig);
void        sigquit_handler(int sig);
//ultils
void        clean_up(char **args, t_command *commands, int num_cmds);
char        *find_command_path(char *cmd, t_list_env *envp);
int         build_up(t_command *comand, t_list_env *environ);
void        free_env_list(t_list_env *env_list);
int         count_char(char *str, char c);
//parseo
char        *interpret_command(const char *command, t_list_env *envp);
t_command   *parse_commands(char *input, t_list_env *envp, int *num_cmds);
int         check_quotes(char *command);
char		*remove_front_and_back_spaces(char *str);
char        *find_env_value(t_list_env *envp_list, const char *key);
//building
void        ft_unset(char *input, t_list_env **envp);
void        ft_echo(char *comand);
void        ft_pwd(void);
void        ft_env(t_list_env *env, char *command);
void        free_list_export(t_list_env *list);
t_list_env *create_node_export(const char *content);
void        print_list_export(t_list_env *list);
t_list_env *copy_list_export(t_list_env *original);
t_list_env *sort_list_export(t_list_env *head, char *temp);
void        update_content_export(t_list_env *current, const char *key, const char *value);
void        add_or_update_export(t_list_env **head, const char *variable);
void        handle_export_no_args(t_list_env **envp);
void		ft_export(char *input, t_list_env **envp);
void        ft_cd(char *route);
void        close_pipes(int **pipes, int num_cmds);
t_command   *parse_commands(char *input, t_list_env *envp, int *num_cmds);
void        ft_here_doc(char *delimiter, int fd[2]);


#endif // MINISHELL_H
