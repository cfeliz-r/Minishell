/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:56:18 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 14:12:54 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	build_up(t_cmd *comand, t_list_env *environ)
{
	if (handle_pwd(comand, environ) || handle_env(comand, environ)
		|| handle_echo(comand))
	{
		manage_error(0, 0);
		return (1);
	}
	return (0);
}

void	ft_exit(char *exits, t_list_env *envp)
{
	char	**aux;
	int		exit_code;
	char	*tmp;

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
		return ;
	}
	aux_exit(aux, envp);
	printf("exit\n");
	if (aux_count(aux) == 2)
		exit_code = ft_atoi(aux[1]);
	free_list_env(envp);
	exit(exit_code);
}

void	process_input_aux(char *line, t_list_env *envp)
{
	char	*interpreted_line;

	if (line[0] == '\0')
		return ;
	interpreted_line = interpret_command(line, envp, 0);
	if (interpreted_line == NULL || is_blank_line(interpreted_line) == 1)
	{
		manage_error(0, 0);
		free(interpreted_line);
		return ;
	}
	executor(envp, interpreted_line);
	free(interpreted_line);
}

void	process_input(t_list_env *envp)
{
	char	*line;
	char	*aux;

	while (1)
	{
		siginit();
		line = readline(JUNGLE_GREEN "🦧BABUTERM🦧➤ " RESET);
		add_history(line);
		aux = ft_strtrim(line, " ");
		if (aux == NULL)
			exit(0);
		if (ft_parsing(aux) == 0)
		{
			process_input_aux2(aux, line, envp);
			continue ;
		}
		free(aux);
		free(line);
	}
}

void	siginit(void)
{
	struct sigaction	sa_int;

	ft_bzero(&sa_int, sizeof(sa_int));
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_int.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_int, NULL);
}
