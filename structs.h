/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:59:47 by manufern          #+#    #+#             */
/*   Updated: 2024/09/16 14:21:44 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

typedef struct s_list_envp
{
	char				*data;
	struct s_list_envp	*next;
}	t_list_env;
typedef struct s_cmd
{
	char	**args;
	char	*cmd_cpt;
	char	*path;
	char	*inredir;
	char	*heredoc_file;
	char	**delimiters;
	char	**outredirs;
	int		out_index;
	int		hdc_index;
	int		appd_out;
	int		flag;
	int		expand_heredoc;
	int		last_redir_flag;
}	t_cmd;

typedef struct s_parse_context
{
	size_t	i;
	size_t	j;
	size_t	in_single_quotes;
	size_t	in_double_quotes;
	size_t	buffer_size;
	size_t	in_heredoc;
	char	*result;
	int		can_expand;
}	t_parse_context;

typedef struct s_quote_context
{
	int	in_single_quotes;
	int	in_double_quotes;
}	t_quote_context;

typedef struct s_split_context
{
	size_t	len;
	char	**commands;
	char	*current_command;
	size_t	i;
	size_t	j;
	size_t	cmd_idx;
	int		in_single_quotes;
	int		in_double_quotes;
}	t_split_context;

typedef struct s_quote_remover
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*result;
	int		in_single_quote;
	int		in_double_quote;
}	t_quote_remover;

typedef struct s_cmd_vars
{
	int					**pipes;
	int					i;
	char				**env_array;
	struct sigaction	sa_ignore;
	int					status;
	pid_t				pid;
	int					exit_status;
	pid_t				pid_last;
}	t_cmd_vars;

typedef struct s_split_commands
{
	size_t			len;
	char			**commands;
	char			*current_command;
	t_quote_context	ctx;
	size_t			i;
	size_t			j;
	size_t			cmd_idx;
}	t_split_commands;

typedef struct s_vars
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	int		last_char_was_space;
	size_t	str_len;
	char	*new_str;
}	t_vars;

typedef struct s_process
{
	t_cmd		*command;
	int			i;
	int			num_cmds;
	char		**env_array;
	t_list_env	*envp;
	int			**pipes;
}	t_process;

typedef struct s_reduce_vars
{
	int		i;
	int		j;
	int		last_char_was_space;
	int		len;
	int		in_quotes;
	char	*new_str;
}	t_reduce_vars;

#endif
