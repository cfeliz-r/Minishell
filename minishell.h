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

t_command *init_commands(char **command_strings, int num_cmds);
char *ft_redir_cmd(char *input, t_list_env *envp);
t_command *clean_up_and_return(char **command_strings, t_command *commands, int num_cmds);
int validate_command(t_command *command, t_list_env *envp);

void handle_redir(char *command_with_redirections, t_command *command);

//lists
t_list_env  *create_list_envp(char **envp);
void clean_up_aux(t_command **commands);
void free_command(t_command *command);
void handle_redirections(t_command *command);

//signals
void        sigint_handler_2(int sig);
void        sigint_handler(int sig);
void        sigquit_handler(int sig);
//ultils
void        clean_up(char **args, t_command *commands, int num_cmds);
char		*find_command_path(char *cmd, t_list_env *envp);
int			build_up(char *comand, t_list_env *environ);
void		execute_commands(t_list_env *list, char *cmd);
void		free_env_list(t_list_env *env_list);
int			count_char(char *str, char c);
//parseo
char        *interpret_command(char *command);
t_command   *parse_commands(char *input, t_list_env *envp, int *num_cmds);
int         check_quotes(char *command);
char		*remove_front_and_back_spaces(char *str);
//building
void		ft_echo(const char *comand);
void        ft_pwd(void);
void        ft_env(t_list_env *env);
void        ft_cd(char *route, t_list_env *env);
t_command   *parse_commands(char *input, t_list_env *envp, int *num_cmds);
void        close_pipes(t_command *commands, int num_cmds);
void        prepare_commands(t_command *commands, int num_cmds, t_list_env *envp);



#endif // MINISHELL_H
