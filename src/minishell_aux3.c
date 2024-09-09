/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:02:12 by manufern          #+#    #+#             */
/*   Updated: 2024/09/09 11:42:57 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	process_input_aux2(char *aux, char *line, t_list_env *envp)
{
	if (aux == NULL || ft_strncmp(aux, "exit ", 5) == 0
		|| ft_strcmp(aux, "\"exit\"") == 0
		|| ft_strcmp(aux, "'exit'") == 0
		|| ft_strcmp(aux, "exit") == 0)
	{
		ft_exit(aux);
		free(aux);
		return ;
	}
	free(line);
	line = ft_put_spaces(aux);
	process_input_aux(line, envp);
	free(line);
	free(aux);
}
