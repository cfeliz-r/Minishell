/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:45:49 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 14:25:40 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define JUNGLE_GREEN "\001\033[38;5;34m\002"
# define RESET "\001\033[0m\002"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "structs.h"
# include <errno.h>
# include <limits.h>
# include "libft/libft.h"
# include <signal.h>
# include <sys/ioctl.h>

extern int	g_stop_status;

void		aux_exit(char **aux, t_list_env *envp);
void		free_list_env(t_list_env *list);
int			is_around(char *str, int pos);
void		update_flag(t_cmd *command);
void		handle_double_quotes(t_vars *vars, char *str);
void		handle_spaces_and_chars(const char *str, t_reduce_vars *vars);
int			is_blank_line(const char *line);
int			validate_identifier(const char *str);
char		*get_env_var_value(t_list_env *envp_list, const char *var_name);
int			has_equal_sign(const char *str);
int			validate_export_identifier(char *str);
void		update_pwd(t_list_env *nodess, char *home);
void		process_single_char_cases(t_vars *vars, char *str);
void		manage_commands_three(t_cmd *cmd, int ncmds, t_list_env *envp,
				t_cmd_vars *vars);
void		init_process2(t_process *ctx, int i, int n_cmd, char **env_arr);
void		init_process1(t_process *ctx, t_cmd *commands, int i, int **pipes);
void		init_process(t_process *ctx, int i, int num_cmds, t_list_env *envp);
void		aux_split(const char *input, t_split_commands *ctx);
char		*append_char(char *result, char c, size_t *j, size_t *buffer_size);
char		*handle_dollar_sign(const char *command,
				t_parse_context *ctx, t_list_env *envp);
void		aux_hadle_dollar(const char *command, t_parse_context *ctx);
void		aux_process(const char *cmd, t_parse_context *ctx,
				t_list_env *envp);
void		process_input_aux(char *line, t_list_env *envp);
void		ft_exit(char *exits, t_list_env *envp);
void		process_input_aux2(char *aux, char *line, t_list_env *envp);
int			check_sintax_and_errors(char *line);
int			compare_until_equal_sign(const char *str, const char *target);
int			handle_unset(t_cmd *comand, t_list_env **environ);
int			handle_stop_condition(char *input_line, t_cmd *cmd, int fd);
char		*generate_temp_file_name(void);
int			open_temp_file(char **temp_file_name);
int			handle_output_files(t_cmd *command);
int			handle_input_files(t_cmd *command);
void		process_delimiter(char **split_result,
				t_cmd *command, int *i, int *j);
char		*remove_quotes_echo(const char *command);
void		process_more_info(char **split_result, t_cmd *command, int *i);
void		allocate_and_fill_outredirs(char **split_result,
				t_cmd *command, int count);
int			count_valid_redirections(char **split_result);
int			is_within_quotes(const char *text, int index);
void		sigint_handler_here_doc(int sig);
char		*correct_strstr(const char *str, const char *to_find);
int			search_string_outside_quotes(const char *text,
				const char *search);
char		*ft_put_spaces(char *str);
char		*safe_strjoin_free(char *s1, const char *s2);
char		*split_quotes(char *str);
int			ft_count(char **split_result);
void		initialize_output_redirection(char **output_redirection,
				t_cmd *command);
void		setup_signal_handler(struct sigaction *sa_int);
void		setup_pipes(int **pipes, int num_cmds);
void		remove_quotes_from_args(char **args);
void		child_process(t_process *ctx);
void		execute_command(t_cmd *command, char **env_array, t_list_env *envp);
int			is_space(int c);
void		print_parts(char **str, int start_index, int *first_part);
char		*strip_quotes(char *str);
char		**split_special(const char *input);
void		split_and_add_commands(const char *input, t_split_context *ctx);
void		init_vars(t_split_context *ctx);
int			is_separator(const char *input, t_split_context *ctx);
void		handle_quotes_and_spaces(const char *input, t_split_context *ctx);
void		init_memory(const char *input, t_split_context *ctx);
int			is_n_option(char *str);
void		clean_up_echo(char **arr);
int			handle_quotes_3(char **start);
void		process_input(t_list_env *envp);
int			all_is_space(char *start, char *end);
int			has_space(char *start, char *end);
int			validate_arguments(char *line);
void		exit_with_error(const char *message, int exit_code);
char		*remove_spaces(const char *str);
int			check_syntax(char *line);
int			check_redirections(char *line);
int			check_quotes(char *command);
int			contains_quotes(const char *str);
int			handle_initial_checks(char *line, char **aux);
int			check_quotes_and_special_chars(char *line);
int			check_redirections_and_syntax(char *line);
int			handle_syntax_checks(char *line);
int			contains_quotes(const char *str);
int			is_builtin_command(char *cmd);
void		prepare_commands(t_cmd *commands, int num_cmds, t_list_env *envp);
int			ft_parsing(char *line);
void		process_redirections(t_cmd *command);
int			handle_export(t_cmd *comand, t_list_env *environ);
void		siginit(void);
int			process_here_doc(t_cmd *command, t_list_env *envp);
void		sigint_handler_ha(int sig);
int			handle_cd(t_cmd *comand, t_list_env *environ);
int			handle_echo(t_cmd *comand);
int			handle_env(t_cmd *comand, t_list_env *environ);
int			handle_pwd(t_cmd *comand, t_list_env *environ);
size_t		aux_count(char **array);
int			all_digits(const char *str);
char		**convert_envp_to_array(t_list_env *envp);
int			validate_command(t_cmd *command, t_list_env *envp);
int			manage_error(int error_code, int return_value);
void		executor(t_list_env *list, char *cmd);
t_list_env	*create_list_envp(char **envp);
void		clean_up_aux(t_cmd **commands);
void		free_command(t_cmd *command);
int			handle_redirections(t_cmd *command);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		clean_up(char **args, t_cmd *commands, int num_cmds);
char		*find_command_path(char *cmd, t_list_env *envp);
int			build_up(t_cmd *comand, t_list_env *environ);
char		*interpret_command(const char *command,
				t_list_env *envp, int can_expand);
char		*find_env_value(t_list_env *envp_list, const char *key);
void		ft_unset(char *input, t_list_env **envp);
void		ft_echo(char *comand);
void		ft_pwd(t_list_env **envp);
void		ft_env(t_list_env *env, char *command);
void		ft_export(char *input, t_list_env **envp);
void		ft_cd(char *route, t_list_env **envp);
void		close_pipes(int **pipes, int num_cmds);
t_cmd		*parse_commands(char *input, int *num_cmds);

#endif
