/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:09:04 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/16 14:21:44 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list_env	*create_list_envp(char **envp)
{
	t_list_env	*envp_list;
	char		*content;
	int			i;

	i = 0;
	envp_list = NULL;
	content = NULL;
	while (envp[i] != NULL)
	{
		content = ft_strdup(envp[i]);
		ft_lstadd_back(&envp_list, ft_lstnew(content));
		i++;
	}
	return (envp_list);
}

int	validate_export_identifier(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		return (manage_error(1, 0), 0);
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (str[i] == '-' && (str[i + 1] == '=' || str[i + 1] == '\0'))
			{
				ft_putstr_fd("not a valid identifier\n", 2);
				return (manage_error(1, 0), 0);
			}
			ft_putstr_fd("not a valid identifier\n", 2);
			return (manage_error(1, 0), 0);
		}
		i++;
	}
	if (!has_equal_sign(str))
		return (0);
	return (1);
}

char	*get_env_var_value(t_list_env *envp_list, const char *var_name)
{
	t_list_env	*current;
	char		*env_var;
	size_t		len;

	if (!envp_list || !var_name)
		return (NULL);
	len = ft_strlen(var_name);
	current = envp_list;
	while (current)
	{
		env_var = current->data;
		if (ft_strncmp(env_var, var_name, len) == 0 && env_var[len] == '=')
			return (env_var + len + 1);
		current = current->next;
	}
	return (NULL);
}
