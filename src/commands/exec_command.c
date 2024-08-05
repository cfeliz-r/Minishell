/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:57:14 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/04 10:00:06 by manuel           ###   ########.fr       */
=======
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:57:14 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/05 10:18:54 by cfeliz-r         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

static int count_envp(t_list_env *envp)
{
    int count;
    
    count = 0;
    if (envp == NULL)
        count = -1;
    while (envp)
    {
        count ++;
        envp = envp->next;
    }
    return count;
}

static char **convert_envp_to_array(t_list_env *envp)
{
    int i = 0;
    int count;
    
    count = count_envp(envp);
    if(count == -1)
        return (NULL);
    char **env_array = malloc((count + 1) * sizeof(char *));
    if (!env_array)
        return NULL;

    while (envp)
    {
        env_array[i] = ft_strdup(envp->envp_content);
        if (!env_array[i])
        {
			clean_up(env_array, NULL, 0);   
            return NULL;
        }
        envp = envp->next;
        i++;
    }
    env_array[i] = NULL;
    return env_array;
}

void prepare_commands(t_command *commands, int num_cmds, t_list_env *envp)
{
    int         i;
    char        **env_array;
    struct sigaction sa_quit;
    struct sigaction sa_int;
     
    i = 0;
    env_array = convert_envp_to_array(envp);
    while (i < num_cmds) {
        if (i < num_cmds - 1 && pipe(commands[i].pipefd) == -1) {
            perror("pipe");
            return;
        }
        commands[i].pid = fork();
        if (commands[i].pid == -1) {
            perror("fork");
            return;
        }
        if (commands[i].pid == 0) {
            sa_quit.sa_handler = SIG_DFL;
            sa_quit.sa_flags = 0;
            sigaction(SIGQUIT, &sa_quit, NULL);
            if (i > 0)
                dup2(commands[i - 1].pipefd[0], STDIN_FILENO);
            if (i < num_cmds - 1)
                dup2(commands[i].pipefd[1], STDOUT_FILENO);
            close_pipes(commands, num_cmds);
            
            handle_redirections(&commands[i]);

            if (execve(commands[i].path, commands[i].args, env_array) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        i++;
    }
    sa_int.sa_handler = sigint_handler_2;
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    close_pipes(commands, num_cmds);
    i = -1;
    while (++i < num_cmds)
        waitpid(commands[i].pid, NULL, 0);
    clean_up(env_array, NULL, 0);
}

void execute_commands(t_list_env *envp, char *cmd)
{
    t_command *commands;
    int num_cmds;
    int i;

    commands = parse_commands(cmd, envp, &num_cmds);
    if (!commands) {
        clean_up(NULL, commands, num_cmds);
        return;
    }

    prepare_commands(commands, num_cmds, envp);
    i = -1;
    while (++i < num_cmds)
        free_command(&commands[i]);
}
