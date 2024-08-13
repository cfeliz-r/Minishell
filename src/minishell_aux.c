/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:54:58 by manufern          #+#    #+#             */
/*   Updated: 2024/08/13 09:55:28 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
