/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:44 by manufern          #+#    #+#             */
/*   Updated: 2024/09/03 16:38:30 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* static void	skip_whitespace(const char **ptr)
{
	while (is_space((unsigned char)**ptr))
		(*ptr)++;
}

static char	*handle_quotes(const char **ptr, int *inside_quotes)
{
	char	quote;
	char	*var_end;

	if (**ptr == '"' || **ptr == '\'')
	{
		quote = *(*ptr)++;
		*inside_quotes = 1;
		var_end = strchr(*ptr, quote);
		if (var_end)
			var_end++;
		else
			var_end = (char *)(*ptr) + strlen(*ptr);
	}
	else
		var_end = (char *)*ptr;
	return (var_end);
}

static void	process_variable_end(char *var_start,
	char *var_end, t_list_env **envp)
{
	char	*variable;

	if (var_start < var_end)
	{
		variable = strndup(var_start, var_end - var_start);
		if (variable)
		{
			add_or_update_export(envp, variable);
			free(variable);
		}
	}
}

static void	process_variable(const char **ptr, t_list_env **envp)
{
	char	*var_start;
	char	*var_end;
	int		inside_quotes;

	while (**ptr)
	{
		skip_whitespace(ptr);
		var_start = (char *)*ptr;
		inside_quotes = 0;
		var_end = handle_quotes(ptr, &inside_quotes);
		if (!inside_quotes)
		{
			while (**ptr && (!is_space((unsigned char)**ptr)
					|| inside_quotes))
			{
				if (**ptr == '"' || **ptr == '\'')
					inside_quotes = !inside_quotes;
				(*ptr)++;
			}
			var_end = (char *)*ptr;
		}
		process_variable_end(var_start, var_end, envp);
	}
} */

int compare_until_equal_sign(const char *str, const char *target)
{
    size_t i = 0;

    while (str[i] != '=' && str[i] != '\0')
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
    if (str[i] == '=')
        return (1);
    return (0);
}

void add_export(const char *input, t_list_env **envp)
{
    char *aux;
    int i;

    i = 0;
    while (is_space((unsigned char)input[i]))
        i++;
    aux = ft_strdup(&input[i]);

    while (*envp != NULL)
    {
        if (compare_until_equal_sign((const char *)(*envp)->envp_content, (const char *)aux) == 1)
        {
            free((*envp)->envp_content);
            (*envp)->envp_content = ft_strdup(aux);
            free(aux);
            return ;
        }
        envp = &(*envp)->next;
    }
    ft_lstadd_back(envp, ft_lstnew(aux));
}

void	ft_export(char *input, t_list_env **envp)
{
	const char	*ptr;

	if (!input || !envp)
		return ;
	if (ft_strcmp(input, "export") == 0 && (input[6] == '\0'
			|| is_space((unsigned char)input[6])))
		handle_export_no_args(envp);
	else if (ft_strncmp(input, "export ", 7) == 0)
	{
		ptr = input + 7;
 		add_export(ptr, envp);
		/* process_variable(&ptr, envp); */
	}
}
