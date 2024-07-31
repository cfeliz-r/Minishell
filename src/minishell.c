/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:56:18 by manufern          #+#    #+#             */
/*   Updated: 2024/07/31 14:39:22 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_decorative_text(void)
{
	printf(
		DARK_FOREST "╔════════════════════════════════════════════════════════════════════════╗\n" RESET
		FOREST_GREEN "║" "▄▄▄▄    ▄▄▄       ▄▄▄▄    █    ██ ▄▄▄█████▓▓█████  ██▀███   ███▄ ▄███▓" FOREST_GREEN "  ║\n" RESET
		LUSH_GREEN "║" "▓█████▄ ▒████▄    ▓█████▄  ██  ▓██▒▓  ██▒ ▓▒▓█   ▀ ▓██ ▒ ██▒▓██▒▀█▀ ██▒" LUSH_GREEN " ║\n" RESET
		DARK_FOREST "║" "▒██▒ ▄██▒██  ▀█▄  ▒██▒ ▄██▓██  ▒██░▒ ▓██░ ▒░▒███   ▓██ ░▄█ ▒▓██    ▓██░" DARK_FOREST " ║\n" RESET
		FOREST_GREEN "║" "▒██░█▀  ░██▄▄▄▄██ ▒██░█▀  ▓▓█  ░██░░ ▓██▓ ░ ▒▓█  ▄ ▒██▀▀█▄  ▒██    ▒██ " FOREST_GREEN " ║\n" RESET
		LUSH_GREEN "║" "░▓█  ▀█▓ ▓█   ▓██▒░▓█  ▀█▓▒▒█████▓   ▒██▒ ░ ░▒████▒░██▓ ▒██▒▒██▒   ░██▒" LUSH_GREEN " ║\n" RESET
		BRIGHT_JUNGLE "║" "░▒▓███▀▒ ▒▒   ▓▒█░░▒▓███▀▒░▒▓▒ ▒ ▒   ▒ ░░   ░░ ▒░ ░░ ▒▓ ░▒▓░░ ▒░   ░  ░" BRIGHT_JUNGLE " ║\n" RESET
		BRIGHT_JUNGLE "║" "▒░▒   ░   ▒   ▒▒ ░▒░▒   ░ ░░▒░ ░ ░     ░     ░ ░  ░  ░▒ ░ ▒░░  ░      ░" BRIGHT_JUNGLE " ║\n" RESET
		FOREST_GREEN "║" " ░    ░   ░   ▒    ░    ░  ░░░ ░ ░   ░         ░     ░░   ░ ░      ░   " FOREST_GREEN " ║\n" RESET
		LUSH_GREEN "║" " ░            ░  ░ ░         ░                 ░  ░   ░            ░   " LUSH_GREEN " ║\n" RESET
		DARK_FOREST "║" "      ░                 ░                                              " DARK_FOREST " ║\n" RESET
		DARK_FOREST "╚════════════════════════════════════════════════════════════════════════╝\n" RESET
	);
}
t_comand_before_pip *create_new_node(char *argv) 
{
	t_comand_before_pip *new_node;

	new_node = malloc(sizeof(t_comand_before_pip));
	if (new_node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_node->comand_complete = argv;
	new_node->next = NULL;
	new_node->comand_afeter_pip = NULL;
	return new_node;
}

int	build_up(char *comand, t_list_env *environ)
{

	if (ft_strcmp(comand, "pwd") == 0)
	{
		ft_pwd();
		return (1);
	}
	else if (ft_strcmp(comand, "env") == 0)
	{
		ft_env(environ);
		return (1);
	} 
	else if (ft_strncmp(comand, "echo ", 5) == 0)
	{
		ft_echo(comand);
		return (1);
	}
	else if (ft_strncmp(comand, "cd ", 3) == 0 || ft_strncmp(comand, "cd\0", 3) == 0)
	{
		ft_cd(comand, environ);
		return (1);
	}
	return (0);
}

char *get_prompt(void)
{
	char cwd[1024];
	char *prompt = NULL;
	char *prefix = JUNGLE_GREEN "🦧BABUTERM🦧➤ " RESET;
	char *suffix = BRIGHT_JUNGLE " ➤ " RESET;
	char *temp;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		exit(1);
	}
	prompt = ft_strjoin(prefix, cwd);
	
	if (prompt == NULL)
	{
		perror("ft_strjoin failed");
		exit(1);
	}

	temp = ft_strjoin(prompt, suffix);
	free(prompt);
	if (temp == NULL)
	{
		perror("ft_strjoin failed");
		exit(1);
	}
	return temp;
}

t_list_env *create_list_envp(char **envp)
{
	t_list_env *envp_list;
	char *content;
	int i;

	i = 0;
	envp_list = NULL;
	content = NULL;
	while (envp[i] != NULL)
	{
		content = ft_strdup(envp[i]);
		ft_lstadd_back(&envp_list, ft_lstnew(content));
		i++;
	}

	return envp_list;
}

void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char *interpret_command(char *command)
{
    int i;
    int j;
    int in_double_quotes;
    int in_single_quotes;
    char *result;

    i = 0;
    j = 0;
    in_double_quotes = 0;
    in_single_quotes = 0;
    result = malloc(ft_strlen(command) + 1);
    if (!result)
        return (NULL);
    while (command[i] != '\0')
    {
        if (command[i] == '"' && !in_single_quotes)
        {
            if (in_double_quotes && i > 0 && command[i - 1] == ' ')
            {
                free(result);
                return (NULL);
            }
            in_double_quotes = !in_double_quotes;
            i++;
        }
        else if (command[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
            i++;
        }
        else
        {
            result[j++] = command[i++];
        }
    }
    result[j] = '\0';
    return (result);
}

void process_input(t_list_env *envp)
{
    char *line;
    int i;
	char *interpreted_line;

    line = readline(JUNGLE_GREEN "🦧BABUTERM🦧➤ " RESET);
    add_history(line);
    if (line == NULL || ft_strcmp(line, "exit") == 0)
    {
        if (line)
            free(line);
        printf("exit\n");
        return;
    }
    i = check_quotes(line);
    if (i == 0)
    {
        free(line);
        perror("quotes error\n");
        process_input(envp);
    }
    else
    {
		interpreted_line = interpret_command(line);
        if (interpreted_line == NULL)
        {
            free(line);
            process_input(envp);
        }
        if (build_up(interpreted_line, envp) == 0)
            execute_commands(envp, interpreted_line);
        free(interpreted_line);
        free(line);
        process_input(envp);
    }
}


int main(int argc, char **argv, char **envp)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;
	t_list_env *envp_list;

	(void)argv;
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);

	envp_list = NULL;
	if (argc > 1)
	{
		perror("ERROR: TOO MANY ARGUMENTS");
		return (EXIT_FAILURE);
	}
	envp_list = create_list_envp(envp);
	print_decorative_text();
	process_input(envp_list);
	free_env_list(envp_list);
	return (0);
}
