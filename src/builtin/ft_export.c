/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:44 by manufern          #+#    #+#             */
/*   Updated: 2024/09/12 17:05:05 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	compare_until_equal_sign(const char *str, const char *target)
{
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0' && target[i] != '\0')
	{
		if (str[i] == ' ')
		{
			i++;
			continue ;
		}
		if (str[i] != target[i])
			return (0);
		i++;
	}
	if ((str[i] == '=' || str[i] == '\0') && (target[i] == '='
			|| target[i] == '\0'))
		return (1);
	return (0);
}

int	has_equal_sign(const char *str)
{
	int	before;

	before = 0;
	while (*str)
	{
		if (*str == '=')
			return (before);
		if (!before && *str != ' ' && *str != '\t')
			before = 1;
		str++;
	}
	return (0);
}

void	update_or_create(char *str, t_list_env **envp, int found)
{
	t_list_env	*temp;
	char		*aux;

	temp = *envp;
	if (ft_isalpha(str[0]) == 0)
	{
		printf("BABUTERM: export: `%s´: not a valid identifier\n", str);
		return ;
	}
	aux = ft_strdup(str);
	free(str);
	str = strip_quotes(aux);
	printf("str: %s\n", str);
	free(aux);
	while (temp)
	{
		if (compare_until_equal_sign(temp->envp_content, str) == 1)
		{
			free(temp->envp_content);
			temp->envp_content = ft_strdup(str);
			found = 1;
			break ;
		}
		temp = temp->next;
	}
	if (!found)
		ft_lstadd_back(envp, ft_lstnew(ft_strdup(str)));
}

void	add_export(const char *input, t_list_env **envp)
{
	char		**split;
	int			i;
	char		*temp;

	split = split_special(input);
	i = 0;
	while (split[i] != NULL)
	{
		if(split[i][0] == '"' || split[i][0] == '\'')
		{
			temp = ft_strdup(split[i]);
			free(split[i]);
			split[i] = strip_quotes(temp);
			printf("split[i]: %s\n", split[i]);
			free(temp);
		}
		if (split[i][0] == '=')
		{
			printf("BABUTERM: export: `%s´: not a valid identifier\n",
				split[i]);
			i++;
			continue ;
		}
		if (!has_equal_sign(split[i]))
		{
			i++;
			continue ;
		}
		update_or_create(split[i], envp, 0);
		i++;
	}
	clean_up(split, NULL, 0);
}

void	ft_export(char *input, t_list_env **envp)
{
	const char	*ptr;

	if (!input || !envp)
		return ;
	if (ft_strcmp(input, "export") == 0 && (input[6] == '\0'
			|| is_space((unsigned char)input[6])))
		return ;
	else if (ft_strncmp(input, "export ", 7) == 0)
	{
		ptr = input + 7;
		add_export(ptr, envp);
	}
}
