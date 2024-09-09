/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:44:11 by manufern          #+#    #+#             */
/*   Updated: 2024/09/09 10:58:22 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t stop = 0;

static void	process_envp(int argc, char **envp)
{
	t_list_env			*envp_list;
	char				*route;
	char				*home;

	route = malloc(PATH_MAX);
	if (!route)
		exit (1);
	home = malloc(strlen("_ROUTE_BABUTERM_=") + PATH_MAX + 1);
	if (!home)
	{
		free (route);
		exit (1);
	}
	envp_list = create_list_envp(envp);
	getcwd(route, PATH_MAX);
	ft_strcpy(home, "_ROUTE_BABUTERM_=");
	ft_strcat(home, route);
	ft_lstadd_back(&envp_list,
		ft_lstnew(ft_strdup("BABUTERM=CFELIZ-R MANUFERN")));
	ft_lstadd_back(&envp_list, ft_lstnew(home));
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
