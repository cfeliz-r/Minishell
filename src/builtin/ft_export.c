/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:44 by manufern          #+#    #+#             */
/*   Updated: 2024/09/06 11:48:00 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* // Función para contar cuántos argumentos hay
int	count_args(const char *input)
{
	int	count = 0;
	int	in_quotes = 0;

	while (*input)
	{
		// Ignorar espacios fuera de las comillas
		while (is_space((unsigned char)*input))
			input++;
		if (*input == '\0')
			break;

		// Encontrar inicio de argumento
		count++;
		while (*input && (in_quotes || !is_space((unsigned char)*input)))
		{
			if (*input == '"')
				in_quotes = !in_quotes; // Cambiar el estado de estar dentro/fuera de comillas
			input++;
		}
	}
	return count;
}

// Función para separar los argumentos considerando comillas
char	**split_special_export(const char *input)
{
	char	**result;
	int		args_count;
	int		in_quotes = 0;
	int		start, end, arg_len;
	int		i = 0, j = 0;

	args_count = count_args(input); // Contamos los argumentos
	result = (char **)malloc((args_count + 1) * sizeof(char *)); // +1 para el NULL al final

	while (input[i])
	{
		// Ignorar espacios fuera de las comillas
		while (is_space((unsigned char)input[i]))
			i++;
		if (input[i] == '\0')
			break;

		// Guardar el inicio del argumento
		start = i;
		while (input[i] && (in_quotes || !is_space((unsigned char)input[i])))
		{
			if (input[i] == '"')
				in_quotes = !in_quotes; // Cambiar el estado de comillas
			i++;
		}
		end = i;

		// Extraer el argumento sin espacios
		arg_len = end - start;
		result[j] = (char *)malloc((arg_len + 1) * sizeof(char));
		strncpy(result[j], &input[start], arg_len);
		result[j][arg_len] = '\0'; // Null-terminar la cadena
		j++;
	}
	result[j] = NULL; // Añadimos NULL al final

	return result;
} */

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
		if (str[i] != target[i] )
			return (0);
		i++;
	}
	if (str[i] == '=' && str[i] == '\0')
		return (1);
	return (0);
}

int	has_equal_sign(const char *str)
{
	int before = 0;

	// Recorremos la cadena de izquierda a derecha
	while (*str)
	{
		if (*str == '=')
		{
			// Encontramos el signo igual, verificamos si hay algo antes y después de él
			return (before && *(str + 1) != '\0');
		}
		if (!before && *str != ' ' && *str != '\t')
			before = 1; // Hay algo antes del '='
		str++;
	}
	return (0); // No se encontró un '=' con algo antes y después
}

void	add_export(const char *input, t_list_env **envp)
{
	char		**split;
	t_list_env	*temp;
	int			i;
	int			found;

	i = 0;
	split = split_special(&input[i]);
	i = 0;
	while (split[i] != NULL)
	{
		if (has_equal_sign(split[i]) == 0)
		{
			i++;
			continue ;
		}
		temp = *envp;
		found = 0;
		while (temp != NULL)
		{
			if (compare_until_equal_sign((const char *)temp->envp_content,
				(const char *)split[i]) == 1)
			{
				temp->envp_content = ft_strdup(split[i]);
				found = 1;
				break ;
			}
			temp = temp->next;
		}
		if (!found)
			ft_lstadd_back(envp, ft_lstnew(ft_strdup(split[i])));
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
	/* handle_export_no_args(envp); */
}
