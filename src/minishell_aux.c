/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:54:58 by manufern          #+#    #+#             */
/*   Updated: 2024/09/10 10:30:33 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pwd(t_cmd *comand, t_list_env *environ)
{
	if (ft_strncmp(comand->args[0], "pwd ", 4) == 0
		|| ft_strcmp(comand->args[0], "pwd") == 0)
	{
		ft_pwd(&environ);
		return (1);
	}
	return (0);
}

int	handle_env(t_cmd *comand, t_list_env *environ)
{
	if (ft_strncmp(comand->args[0], "env ", 4) == 0
		|| ft_strcmp(comand->args[0], "env") == 0)
	{
		ft_env(environ, comand->cmd_cpt);
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

int	handle_cd(t_cmd *comand, t_list_env *environ)
{
	if (ft_strncmp(comand->cmd_cpt, "cd ", 3) == 0
		||ft_strncmp(comand->cmd_cpt, "'cd' ", 5) == 0
		|| ft_strncmp(comand->cmd_cpt, "\"cd\" ", 5) == 0
		|| ft_strncmp(comand->cmd_cpt, "cd\0", 3) == 0)
	{
		ft_cd(comand->cmd_cpt, &environ);
		return (1);
	}
	return (0);
}

int	handle_export(t_cmd *comand, t_list_env *environ)
{
	if (ft_strncmp(comand->cmd_cpt, "export ", 7) == 0
		||ft_strncmp(comand->cmd_cpt, "'export' ", 9) == 0
		|| ft_strncmp(comand->cmd_cpt, "\"export\" ", 9) == 0
		|| ft_strcmp(comand->cmd_cpt, "export") == 0)
	{
		ft_export(comand->cmd_cpt, &environ);
		return (1);
	}
	return (0);
}
