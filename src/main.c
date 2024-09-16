/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:44:11 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 14:24:59 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_stop_status = 0;

static char	*find_env_var(t_list_env *envp_list, const char *var_name)
{
	while (envp_list)
	{
		if (ft_strncmp(envp_list->data,
				var_name, ft_strlen(var_name)) == 0)
			return (envp_list->data);
		envp_list = envp_list->next;
	}
	return (NULL);
}

void	update_env_var(t_list_env *envp_list, char *var_name, char *new_value)
{
	t_list_env	*current;
	char		*env_var;
	size_t		len;
	char		*tmp;

	if (!envp_list || !var_name || !new_value)
		return ;
	len = ft_strlen(var_name);
	current = envp_list;
	while (current)
	{
		env_var = current->data;
		if (ft_strncmp(env_var, var_name, len) == 0 && env_var[len] == '=')
		{
			tmp = current->data;
			current->data = ft_strjoin(var_name, "=");
			free(tmp);
			tmp = current->data;
			current->data = ft_strjoin(current->data, new_value);
			free(tmp);
			return ((void)free(new_value));
		}
		current = current->next;
	}
	ft_lstadd_back(&envp_list, ft_lstnew(ft_strdup("SHLVL=1")));
}

static void	update_envp_list(t_list_env **envp_list, char *home)
{
	char	*shlvl_str;
	int		shlvl;

	if (!find_env_var(*envp_list, "BABUTERM"))
		ft_lstadd_front(envp_list,
			ft_lstnew(ft_strdup("BABUTERM=CFELIZ-R MANUFERN")));
	if (!find_env_var(*envp_list, "_ROUTE_BABUTERM_"))
		ft_lstadd_front(envp_list, ft_lstnew(home));
	shlvl_str = get_env_var_value(*envp_list, "SHLVL");
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str);
		shlvl++;
		update_env_var(*envp_list, "SHLVL", ft_itoa(shlvl));
	}
	if (!find_env_var(*envp_list, "SHLVL"))
		ft_lstadd_back(envp_list, ft_lstnew(ft_strdup("SHLVL=1")));
}

static void	process_envp(int argc, char **envp)
{
	t_list_env	*envp_list;
	char		*route;
	char		*home;

	if (argc != 1)
		return ;
	route = malloc(PATH_MAX);
	if (!route)
		exit(1);
	home = malloc(PATH_MAX);
	if (!home)
		exit(1);
	envp_list = create_list_envp(envp);
	if (getcwd(route, PATH_MAX) == NULL)
		exit(1);
	ft_strcpy(home, "_ROUTE_BABUTERM_=");
	ft_strcat(home, route);
	update_envp_list(&envp_list, home);
	free(route);
	process_input(envp_list);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	(void)argv;
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	process_envp(argc, envp);
	return (0);
}
