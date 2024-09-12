/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:09:04 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/12 18:35:42 by manufern         ###   ########.fr       */
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
	if (str[0] == '=')
	{
		manage_error(1, 0);
		printf("export: `%s`: not a valid identifier\n", str);
		return (0);
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
		env_var = current->envp_content;
		if (ft_strncmp(env_var, var_name, len) == 0 && env_var[len] == '=')
			return (env_var + len + 1);
		current = current->next;
	}
	return (NULL);
}
