/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:44:11 by manufern          #+#    #+#             */
/*   Updated: 2024/09/03 12:19:15 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t stop = 0;

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	t_list_env			*envp_list;

	printf("argc: %d\n", argc);
	(void)argv;
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	envp_list = create_list_envp(envp);
	if (argc == 1)
		process_input(envp_list);
	return (0);
}
