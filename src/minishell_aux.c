/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:54:58 by manufern          #+#    #+#             */
/*   Updated: 2024/08/19 11:58:41 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pwd(t_command *comand)
{
	if (ft_strncmp(comand->args[0], "pwd ", 4) == 0 || ft_strcmp(comand->args[0], "pwd") == 0)
	{
		ft_pwd();
		return (1);
	}
	return (0);
}

/* Función para manejar el comando env */
int	handle_env(t_command *comand, t_list_env *environ)
{
	if (ft_strncmp(comand->args[0], "env ", 4) == 0 || ft_strcmp(comand->args[0], "env") == 0)
	{
		ft_env(environ, comand->args[0]);
		return (1);
	}
	return (0);
}

/* Función para manejar el comando echo */
int	handle_echo(t_command *comand)
{
	if (ft_strncmp(comand->args[0], "echo ", 5) == 0 || ft_strcmp(comand->args[0], "echo") == 0)
	{
		ft_echo(comand->args);
		return (1);
	}
	return (0);
}

int	handle_cd(t_command *comand)
{
	if (ft_strncmp(comand->cmd_cpt, "cd ", 3) == 0
	||ft_strncmp(comand->cmd_cpt, "'cd' ", 5) == 0 || ft_strncmp(comand->cmd_cpt, "\"cd\" ", 5) == 0
		|| ft_strncmp(comand->cmd_cpt, "cd\0", 3) == 0)
	{
		ft_cd(comand->cmd_cpt);
		return (1);
	}
	return (0);
}

int	handle_export(t_command *comand, t_list_env *environ)
{
	if (ft_strncmp(comand->cmd_cpt, "export ", 7) == 0
	||ft_strncmp(comand->cmd_cpt, "'export' ", 9) == 0 || ft_strncmp(comand->cmd_cpt, "\"export\" ", 9) == 0
		|| ft_strcmp(comand->cmd_cpt, "export") == 0)
	{
		ft_export(comand->cmd_cpt, &environ);
		return (1);
	}
	return (0);
}
