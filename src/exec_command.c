/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:57:14 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/07/29 16:22:05 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

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
			clean_up(env_array, NULL);   
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

    i = 0;
    env_array = convert_envp_to_array(envp);
    while (i < num_cmds)
    {
        if (i < num_cmds - 1 && pipe(commands[i].pipefd) == -1)
        {
            perror("pipe");
            return ;
        }
        commands[i].pid = fork();
        if (commands[i].pid == -1)
        {
            perror("fork");
            return;
        }
        if (commands[i].pid == 0)
        {
            if (i > 0)
                dup2(commands[i - 1].pipefd[0], STDIN_FILENO);
            if (i < num_cmds - 1)
                dup2(commands[i].pipefd[1], STDOUT_FILENO);
            close_pipes(commands, num_cmds);
            if (execve(commands[i].path, commands[i].args, env_array) == -1)
            {
                perror("execve");
                return ;
            }
        }
        i++;
    }
    close_pipes(commands, num_cmds);
    i = -1;
    while (++i < num_cmds)
        waitpid(commands[i].pid, NULL, 0);
    clean_up(env_array, NULL);
}


void execute_commands(t_list_env *envp, char *cmd)
{
    t_command *commands;
    int     num_cmds;
    int     i;
    commands = parse_commands(cmd, envp, &num_cmds);
    if (!commands)
        return ;
    prepare_commands(commands, num_cmds, envp);
    i = -1;
    while (++i < num_cmds)
        clean_up(commands[i].args, commands[i].path);
    free(commands);
}
