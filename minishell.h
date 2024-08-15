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



int ft_parsing(char *line);
//redirectios
void handle_hdoc(char *heredoc_redirection, t_command *command);
void process_redirections(char *command_with_redirections, t_command *command);
void handle_output_redirection(char *output_redirection, t_command *command);
void handle_input_redirection(char *input_redirection, t_command *command);

int	handle_export(t_command *comand, t_list_env *environ);
void	siginit(void);


void sigint_handler_ha(int sig);
int	handle_cd(t_command *comand);
int	handle_echo(t_command *comand);
int	handle_env(t_command *comand, t_list_env *environ);
int	handle_pwd(t_command *comand);
size_t aux_count(char **array);
int all_digits(const char *str);
int process_here_doc(char *delimiter);
void handle_heredoc(t_command *commands, int i);
void        setup_signals(void);
int         count_envp(t_list_env *envp);
char        **convert_envp_to_array(t_list_env *envp);
t_command   *init_commands(char **command_strings, int num_cmds);
char        *ft_redir_cmd(char *input, t_list_env *envp);
t_command   *clean_up_and_return(char **command_strings, t_command *commands, int num_cmds);
int         validate_command(t_command *command, t_list_env *envp);
int         manage_error(int error_code, int return_value);
void        handle_key_redir(char *command_with_redirections, t_command *command);
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
void        prepare_commands(t_command *commands, int num_cmds, t_list_env *envp);

#endif // MINISHELL_H
