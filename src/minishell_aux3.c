/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:02:12 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 13:39:45 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	process_input_aux2(char *aux, char *line, t_list_env *envp)
{
	if (ft_strchr(aux, '|') == 0
		&& (aux == NULL || ft_strncmp(aux, "exit ", 5) == 0
			|| ft_strcmp(aux, "\"exit\"") == 0
			|| ft_strcmp(aux, "'exit'") == 0
			|| ft_strcmp(aux, "exit") == 0))
	{
		ft_exit(aux, envp);
		free(aux);
		free(line);
		return ;
	}
	free(line);
	line = ft_put_spaces(aux);
	process_input_aux(line, envp);
	free(line);
	free(aux);
}

int	handle_unset(t_cmd *comand, t_list_env **environ)
{
	if (ft_strncmp(comand->cmd_cpt, "unset ", 6) == 0
		||ft_strncmp(comand->cmd_cpt, "'unset' ", 8) == 0
		|| ft_strncmp(comand->cmd_cpt, "\"unset\" ", 8) == 0
		|| ft_strncmp(comand->cmd_cpt, "unset\0", 6) == 0)
	{
		ft_unset(comand->cmd_cpt, environ);
		return (1);
	}
	return (0);
}

void	process_single_char_cases(t_vars *vars, char *str)
{
	if ((str[vars->i] == '|' || str[vars->i] == '<' || str[vars->i] == '>'))
	{
		if (vars->i > 0 && str[vars->i - 1] != ' '
			&& !vars->last_char_was_space)
			vars->new_str[vars->j++] = ' ';
		vars->new_str[vars->j++] = str[vars->i++];
		if (str[vars->i] != ' ' && str[vars->i] != '\0')
			vars->new_str[vars->j++] = ' ';
		vars->last_char_was_space = 1;
	}
	else if (str[vars->i] == ' ')
	{
		vars->new_str[vars->j++] = str[vars->i++];
		vars->last_char_was_space = 1;
	}
	else
	{
		vars->new_str[vars->j++] = str[vars->i++];
		vars->last_char_was_space = 0;
	}
}
