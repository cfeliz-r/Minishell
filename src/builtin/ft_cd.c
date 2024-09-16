/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:54:35 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 14:21:44 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*remove_quotes_cd(char *str)
{
	char	*cleaned_str;
	size_t	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\''))
	{
		cleaned_str = malloc(len - 1);
		if (cleaned_str == NULL)
			return (NULL);
		memcpy(cleaned_str, str + 1, len - 2);
		cleaned_str[len - 2] = '\0';
		return (cleaned_str);
	}
	return (str);
}

void	handle_directory_change(char *cleaned_route, char *original_route)
{
	if (access(cleaned_route, F_OK | R_OK) == 0)
		chdir(cleaned_route);
	else
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		manage_error(1, 0);
	}
	if (cleaned_route != original_route)
		free(cleaned_route);
}

void	handle_memory_error(void)
{
	printf("cd: memory allocation error\n");
	manage_error(1, 0);
}

void	process_route(char *route)
{
	char	**str_route;
	char	*cleaned_route;
	int		i;

	str_route = ft_split(route, ' ');
	i = 0;
	while (str_route[i])
		i++;
	if (i == 2)
	{
		if (str_route[1] != NULL)
		{
			cleaned_route = remove_quotes_cd(str_route[1]);
			if (cleaned_route != NULL)
				handle_directory_change(cleaned_route, str_route[1]);
			else
				handle_memory_error();
		}
	}
	else if (i > 2)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		manage_error(1, 0);
	}
	clean_up(str_route, NULL, 0);
}

void	ft_cd(char *route, t_list_env **envp)
{
	t_list_env	*current;
	t_list_env	*nodess;
	char		home[PATH_MAX];

	current = *envp;
	nodess = *envp;
	manage_error(0, 0);
	process_route(route);
	while (current)
	{
		if (compare_until_equal_sign(current->data,
				"_ROUTE_BABUTERM_") == 1)
		{
			free(current->data);
			ft_strcpy(home, "_ROUTE_BABUTERM_=");
			getcwd(home + 17, PATH_MAX - 17);
			current->data = ft_strdup(home);
			break ;
		}
		current = current->next;
	}
	update_pwd(nodess, home);
}
