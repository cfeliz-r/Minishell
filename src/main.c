/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeliz-r <cfeliz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:44:11 by manufern          #+#    #+#             */
/*   Updated: 2024/09/06 20:02:02 by cfeliz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t stop = 0;

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	t_list_env			*envp_list;
	char				*route;
	char				*home;

	(void)argv;
	route = malloc(PATH_MAX);
	if (!route)
		return (1);
	home = malloc(strlen("_ROUTE_BABUTERM_=") + PATH_MAX + 1);
	if (!home)
	{
		free(route);
		return (1);
	}
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	envp_list = create_list_envp(envp);
	getcwd(route, PATH_MAX);
	ft_strcpy(home, "_ROUTE_BABUTERM_=");
	ft_strcat(home, route);
	ft_lstadd_back(&envp_list, ft_lstnew(ft_strdup("BABUTERM=CFELIZ-R MANUFERN")));
	ft_lstadd_back(&envp_list, ft_lstnew(home));
	free(route);
	if (argc == 1)
		process_input(envp_list);

	return (0);
}
