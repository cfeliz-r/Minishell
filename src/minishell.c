/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:56:18 by manufern          #+#    #+#             */
/*   Updated: 2024/08/06 17:41:10 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void print_decorative_text(void)
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

int	build_up(char *comand, t_list_env *environ)
{

	/* if (ft_strcmp(comand, "pwd") == 0)
	{
		ft_pwd();
		return (1);
	}
	else if (ft_strcmp(comand, "env") == 0)
	{
		ft_env(environ);
		return (1);
	}  */
	if (ft_strncmp(comand, "echo ", 5) == 0)
	{
		ft_echo(comand);
		return (1);
	}
	else if (ft_strncmp(comand, "cd ", 3) == 0 || ft_strncmp(comand, "cd\0", 3) == 0)
	{
		ft_cd(comand, environ);
		return (1);
	}
	else if (ft_strncmp(comand, "export", 6) == 0)
	{
		ft_export(comand, environ);
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

void process_input(t_list_env *envp)
{
    char *line;
    int i;
	char *interpreted_line;

	while(1)
	{
		line = readline(JUNGLE_GREEN "🦧BABUTERM🦧➤ " RESET);
		add_history(line);
		line = remove_front_and_back_spaces(line);
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			if (line)
				free(line);
			printf("exit\n");
			break ;
		}
		i = check_quotes(line);
		if (i == 0)
		{
			free(line);
			perror("quotes error\n");
		}
		else
		{
			interpreted_line = interpret_command(line, envp);
			if (interpreted_line == NULL)
			{
				free(line);
				continue;
			}
			if (build_up(interpreted_line, envp) == 0)
				execute_commands(envp, interpreted_line);
			free(interpreted_line);
			free(line);
		}
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
