/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:56:18 by manufern          #+#    #+#             */
/*   Updated: 2024/08/20 14:27:03 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	build_up(t_command *comand, t_list_env *environ)
{
	if (handle_pwd(comand) || handle_env(comand, environ)
		|| handle_echo(comand)
		|| handle_export(comand, environ))
	{
		return (1);
	}
	return (0);
}

void	ft_exit(char *exits)
{
	char	**aux;
	int		exit_code;

	aux = ft_split(exits, ' ');
	exit_code = 0;
	printf("exit\n");
	if (!aux || aux_count(aux) > 2)
	{
		printf("exit: too many arguments\n");
		manage_error(1, 0);
		clean_up(aux, NULL, 0);
		return ;
	}
	if (aux_count(aux) == 2 && !all_digits(aux[1]))
	{
		printf("exit: %s: numeric argument required\n", aux[1]);
		exit(2);
	}
	if (aux_count(aux) == 2)
		exit_code = ft_atoi(aux[1]);	
	clean_up(aux, NULL, 0);
	exit(exit_code);
}

void	process_input_aux(char	*line, t_list_env *envp)
{
	char	*interpreted_line;
	
	if (line[0] == '\0')
		return ;
	if (ft_strncmp(line, "export ", 7) == 0
	||ft_strcmp(line, "'export'") == 0 || ft_strcmp(line, "\"export\"") == 0
		|| ft_strcmp(line, "export") == 0)
		ft_export(line, &envp);
	if (ft_strncmp(line, "unset ", 6) == 0
	||ft_strcmp(line, "'unset'") == 0 || ft_strcmp(line, "\"unset\"") == 0
		|| ft_strcmp(line, "unset") == 0)
		ft_unset(line, &envp);
	else
	{
		interpreted_line = interpret_command(line, envp);
		if (interpreted_line == NULL)
		{
			free(interpreted_line);
			return ;
		}
		execute_commands(envp, interpreted_line);
		free(interpreted_line);
	}
}

void	process_input(t_list_env *envp)
{
	char	*line;

	while (1)
	{
		siginit();
		line = readline(JUNGLE_GREEN "🦧BABUTERM🦧➤ " RESET);
		add_history(line);
		if (line == NULL)
			exit(0);
		if (ft_parsing(line) == 0)
		{
			if (!line || ft_strncmp(line, "exit ", 5) == 0
			|| ft_strcmp(line, "\"exit\"") == 0 || ft_strcmp(line, "'exit'") == 0
				|| ft_strcmp(line, "exit") == 0)
			{
				else
					ft_exit(line);
				free(line);
				continue ;
			}
			process_input_aux(line, envp);
			free(line);
		}
	}
}
void	siginit(void)
{
	struct sigaction	sa_int;
	//struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_int.sa_handler = SIG_IGN;
	//sa_int.sa_flags = 0;
	sigaction(SIGQUIT, &sa_int, NULL);
}


int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	t_list_env			*envp_list;

	(void)argv;
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	envp_list = create_list_envp(envp);
	if (argc == 1)
		process_input(envp_list);
	return (0);
}
