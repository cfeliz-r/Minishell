/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:56:18 by manufern          #+#    #+#             */
/*   Updated: 2024/08/12 19:03:49 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Función para manejar el comando pwd */
int	handle_pwd(t_command *comand)
{
	if (ft_strncmp(comand->cmd_complete, "pwd ", 4) == 0
		|| ft_strcmp(comand->cmd_complete, "pwd") == 0)
	{
		ft_pwd();
		return (1);
	}
	return (0);
}

/* Función para manejar el comando env */
int	handle_env(t_command *comand, t_list_env *environ)
{
	if (ft_strncmp(comand->cmd_complete, "env ", 4) == 0
		|| ft_strcmp(comand->cmd_complete, "env") == 0)
	{
		ft_env(environ, comand->cmd_complete);
		return (1);
	}
	return (0);
}

/* Función para manejar el comando echo */
int	handle_echo(t_command *comand)
{
	if (ft_strncmp(comand->cmd_complete, "echo ", 5) == 0
		|| ft_strcmp(comand->cmd_complete, "echo") == 0)
	{
		ft_echo(comand->cmd_complete);
		return (1);
	}
	return (0);
}

/* Función para manejar el comando cd */
int	handle_cd(t_command *comand)
{
	if (ft_strncmp(comand->cmd_complete, "cd ", 3) == 0
		|| ft_strncmp(comand->cmd_complete, "cd\0", 3) == 0)
	{
		ft_cd(comand->cmd_complete);
		return (1);
	}
	return (0);
}

/* Función para manejar el comando export */
int	handle_export(t_command *comand, t_list_env *environ)
{
	if (ft_strncmp(comand->cmd_complete, "export ", 7) == 0
		|| ft_strcmp(comand->cmd_complete, "export") == 0)
	{
		ft_export(comand->cmd_complete, &environ);
		return (1);
	}
	return (0);
}

/* Función para manejar los comandos */
int	build_up(t_command *comand, t_list_env *environ)
{
	if (handle_pwd(comand) || handle_env(comand, environ)
		|| handle_echo(comand) || handle_cd(comand)
		|| handle_export(comand, environ))
	{
		return (1);
	}
	return (0);
}

/* Función para manejar el comando exit */
void	ft_exit(char *exits)
{
	char	**aux;
	int		exit_code;

	aux = ft_split(exits, ' ');
	exit_code = 0;
	if (!aux || aux_count(aux) > 2)
	{
		printf("exit: too many arguments\n");
		manage_error(1, 0);
		clean_up(aux, NULL, 0);
		return ;
	}
	if (aux_count(aux) == 2 && !all_digits(aux[1]))
		exit(2);
	if (aux_count(aux) == 2)
		exit_code = ft_atoi(aux[1]);
	printf("exit\n");
	clean_up(aux, NULL, 0);
	exit(exit_code);
}

/* Función para procesar la entrada del usuario */
void	process_input(t_list_env *envp)
{
	char	*line;
	char	*interpreted_line;

	while (1)
	{
		line = readline(JUNGLE_GREEN "🦧BABUTERM🦧➤ " RESET);
		add_history(line);
		line = remove_front_and_back_spaces(line);
		if (!line || ft_strncmp(line, "exit ", 5) == 0
			|| ft_strcmp(line, "exit") == 0)
		{
			if (!line)
			{
				if (line)
					free(line);
				exit(0);
			}
			else
				ft_exit(line);
			free(line);
			continue ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (ft_strncmp(line, "export ", 7) == 0
			|| ft_strcmp(line, "export") == 0)
		{
			ft_export(line, &envp);
		}
		if (check_quotes(line) == 0)
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
				continue ;
			}
			execute_commands(envp, interpreted_line);
			free(interpreted_line);
			free(line);
		}
	}
}

/* Función principal */
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
