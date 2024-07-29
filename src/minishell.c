/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:56:18 by manufern          #+#    #+#             */
/*   Updated: 2024/07/29 19:23:56 by manufern         ###   ########.fr       */
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

// Función para imprimir las variables de entorno


// Función para crear un nuevo nodo de la lista
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

void process_input(t_list_env *envp)
{
	char *line;
	int i;
	
	line = NULL;
	line = readline(JUNGLE_GREEN"🦧BABUTERM🦧➤ "RESET);
	add_history(line);
	i = check_quotes(line);
	if(i == 0)
	{
		free(line);
		perror("quotes error\n");
		process_input(envp);
	}
	
	else if (line == NULL)
		return ;
	else if (ft_strcmp(line, "exit") == 0)
	{
		free(line);
		return ;
	}
	else if (build_up(line, envp) == 0)
		execute_commands(envp, line);
	free(line);
	process_input(envp);
}


int main(int argc, char **argv, char **envp)
{
	t_list_env *envp_list;

	(void)argv;
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
