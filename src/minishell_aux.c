/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:54:58 by manufern          #+#    #+#             */
/*   Updated: 2024/09/04 15:31:18 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pwd(t_cmd *comand)
{
	if (ft_strncmp(comand->args[0], "pwd ", 4) == 0
		|| ft_strcmp(comand->args[0], "pwd") == 0)
	{
		ft_pwd();
		return (1);
	}
	return (0);
}

int	handle_env(t_cmd *comand, t_list_env *environ)
{
	if (ft_strncmp(comand->args[0], "env ", 4) == 0
		|| ft_strcmp(comand->args[0], "env") == 0)
	{
		ft_env(environ, comand->args[0]);
		return (1);
	}
	return (0);
}

int	handle_echo(t_cmd *comand)
{
	if (ft_strncmp(comand->args[0], "echo ", 5) == 0
		|| ft_strcmp(comand->args[0], "echo") == 0)
	{
		ft_echo(comand->cmd_cpt);
		return (1);
	}
	return (0);
}

int	handle_cd(t_cmd *comand)
{
	if (ft_strncmp(comand->cmd_cpt, "cd ", 3) == 0
		||ft_strncmp(comand->cmd_cpt, "'cd' ", 5) == 0
		|| ft_strncmp(comand->cmd_cpt, "\"cd\" ", 5) == 0
		|| ft_strncmp(comand->cmd_cpt, "cd\0", 3) == 0)
	{
		ft_cd(comand->cmd_cpt);
		return (1);
	}
	return (0);
}

int	handle_export(t_cmd *comand, t_list_env *environ)
{
	char	*aux;
	
	aux = remove_quotes_echo(comand->cmd_cpt);
	if (ft_strncmp(aux, "export ", 7) == 0
		||ft_strncmp(aux, "'export' ", 9) == 0
		|| ft_strncmp(aux, "\"export\" ", 9) == 0
		|| ft_strcmp(aux, "export") == 0)
	{
		ft_export(aux, &environ);
		free(aux);
		return (1);
	}
	free(aux);
	return (0);
}
