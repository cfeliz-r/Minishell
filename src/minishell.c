/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:56:18 by manufern          #+#    #+#             */
/*   Updated: 2024/09/19 14:41:34 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int build_up(t_cmd *comand, t_list_env *environ)
{
    if (handle_pwd(comand, environ) || handle_env(comand, environ)
        || handle_echo(comand))
    {
        manage_error(0, 0);
        return (1);
    }
    return (0);
}

void ft_exit(char *exits, t_list_env *envp)
{
    char **aux;
    int exit_code;
    char *tmp;

    aux = ft_split(exits, ' ');
    exit_code = 0;
    if (aux_count(aux) >= 2)
    {
        tmp = aux[1];
        aux[1] = strip_quotes(tmp);
        free(tmp);
    }
    if (aux == NULL || aux_count(aux) > 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        manage_error(1, 0);
        clean_up(aux, NULL, 0);
        return;
    }
    aux_exit(aux, envp);
    printf("exit\n");
    if (aux_count(aux) == 2)
        exit_code = ft_atoi(aux[1]);
    free_list_env(envp);
    exit(exit_code);
}

char *get_git_commit_hash(void) {
    FILE *fp;
    char path[1035];
    char *commit_hash;

    fp = popen("git rev-parse --short HEAD 2>/dev/null", "r");
    if (fp == NULL) {
        return (NULL);
    }
    if (fgets(path, sizeof(path), fp) != NULL) {
        commit_hash = ft_strtrim(path, "\n");
    } else {
        commit_hash = NULL;
    }
    pclose(fp);
    return (commit_hash);
}

void process_input_aux(char *line, t_list_env *envp)
{
    char *interpreted_line;

    if (line[0] == '\0')
        return;
    interpreted_line = interpret_command(line, envp, 0);
    if (interpreted_line == NULL || is_blank_line(interpreted_line) == 1)
    {
        manage_error(0, 0);
        free(interpreted_line);
        return;
    }
    executor(envp, interpreted_line);
    free(interpreted_line);
}

char *get_git_branch(void)
{
    FILE *fp;
    char path[1035];
    char *branch;

    fp = popen("git rev-parse --abbrev-ref HEAD 2>/dev/null", "r");
    if (fp == NULL)
        return (NULL);
    if (fgets(path, sizeof(path), fp) != NULL)
    {
        branch = ft_strtrim(path, "\n");
    }
    else
        branch = NULL;
    pclose(fp);
    return (branch);
}

char *get_git_changes(void)
{
    FILE *fp;
    char path[1035];
    char *changes;

    fp = popen("git status --porcelain 2>/dev/null", "r");
    if (fp == NULL)
        return (NULL);
    if (fgets(path, sizeof(path), fp) != NULL)
    {
        changes = ft_strdup("✎");
    }
    else
        changes = ft_strdup("✔");
    pclose(fp);
    return (changes);
}

void handle_commit(t_list_env *envp) {
    char *commit_message;
    char *git_changes;

    (void)envp;

    git_changes = get_git_changes();
    
    printf("Cambios pendientes:\n%s\n", git_changes);
    
    commit_message = readline("Ingrese el mensaje del commit: ");
    
    if (commit_message && commit_message[0] != '\0') {
        system("git add .");

        char command[256];
        snprintf(command, sizeof(command), "git commit -m \"%s\"", commit_message);
        system(command);
        printf("Commit realizado: %s\n", commit_message);

        system("git push");
        printf("Cambios enviados a la rama remota.\n");
    } else {
        printf("Mensaje de commit vacío. Commit cancelado.\n");
    }

    free(git_changes);
    free(commit_message);
}

void initialize_readline() {
    rl_bind_key('\t', rl_complete); // Asociar la tecla Tab a la función de autocompletación
}

void process_input(t_list_env *envp) {
    char *line;
    char *aux;
    char cwd[PATH_MAX];
    char *prompt;
    char *git_branch;
    char *git_changes;
    char *git_commit_hash;

    initialize_readline(); // Inicializar readline para autocompletación

    while (1) {
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd() error");
            exit(1);
        }

        git_branch = get_git_branch();
        git_changes = get_git_changes();
        git_commit_hash = get_git_commit_hash();

        prompt = ft_strjoin(JUNGLE_GREEN "🦧BABUTERM🦧➤", cwd);
        if (git_branch) {
            prompt = ft_strjoin(prompt, BABY_BLUE " (");
            prompt = ft_strjoin(prompt, git_branch);
            prompt = ft_strjoin(prompt, " ");
            prompt = ft_strjoin(prompt, git_changes);
            prompt = ft_strjoin(prompt, " ");
            if (git_commit_hash) {
                prompt = ft_strjoin(prompt, git_commit_hash);
            }
            prompt = ft_strjoin(prompt, ")");
        }
        prompt = ft_strjoin(prompt, ORANGE "➤ " RESET);

        siginit();
        line = readline(prompt);
        free(prompt);
        free(git_branch);
        free(git_changes);
        free(git_commit_hash);

        if (line == NULL) {
            break; // Manejar la salida
        }

        // Manejar el comando para el commit
        if (strcmp(line, "commit") == 0) {
            handle_commit(envp);
            free(line);
            continue;
        }

        add_history(line);
        aux = ft_strtrim(line, " ");
        if (aux == NULL) {
            free(line);
            exit(0);
        }
        if (ft_parsing(aux) == 0) {
            process_input_aux2(aux, line, envp);
            continue;
        }
        free(aux);
        free(line);
    }

    // ... código existente ...
}

void siginit(void)
{
    struct sigaction sa_int;

    ft_bzero(&sa_int, sizeof(sa_int));
    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    sa_int.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa_int, NULL);
}
