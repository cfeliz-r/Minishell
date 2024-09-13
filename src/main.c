/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:44:11 by manufern          #+#    #+#             */
/*   Updated: 2024/09/13 13:47:16 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_stop_status = 0;

static char	*find_env_var(t_list_env *envp_list, const char *var_name)
{
	while (envp_list)
	{
		if (ft_strncmp(envp_list->envp_content,
				var_name, ft_strlen(var_name)) == 0)
			return (envp_list->envp_content);
		envp_list = envp_list->next;
	}
	return (NULL);
}

void	update_env_var(t_list_env *envp_list, char *var_name, char *new_value)
{
	t_list_env	*current;
	char		*env_var;
	size_t		len;

	if (!envp_list || !var_name || !new_value)
		return ;
	len = ft_strlen(var_name);
	current = envp_list;
	while (current)
	{
		env_var = current->envp_content;
		if (ft_strncmp(env_var, var_name, len) == 0 && env_var[len] == '=')
		{
			free(current->envp_content);
			current->envp_content = ft_strjoin(var_name, "=");
			current->envp_content = ft_strjoin(current->envp_content,
					new_value);
			return ;
		}
		current = current->next;
	}
	ft_lstadd_back(&envp_list, ft_lstnew(ft_strdup("SHLVL=1")));
}

static void	update_envp_list(t_list_env **envp_list, char *home)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = get_env_var_value(*envp_list, "SHLVL");
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str);
		shlvl++;
		update_env_var(*envp_list, "SHLVL", ft_itoa(shlvl));
	}
	if (!find_env_var(*envp_list, "SHLVL"))
		ft_lstadd_back(envp_list, ft_lstnew(ft_strdup("SHLVL=1")));
	if (!find_env_var(*envp_list, "BABUTERM"))
		ft_lstadd_back(envp_list,
			ft_lstnew(ft_strdup("BABUTERM=CFELIZ-R MANUFERN")));
	if (!find_env_var(*envp_list, "_ROUTE_BABUTERM_"))
		ft_lstadd_back(envp_list, ft_lstnew(home));
}

static void	process_envp(int argc, char **envp)
{
	t_list_env	*envp_list;
	char		*route;
	char		*home;

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
	if (argc == 1)
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
