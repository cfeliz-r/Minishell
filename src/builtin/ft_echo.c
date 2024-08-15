/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:47:30 by manufern          #+#    #+#             */
/*   Updated: 2024/08/15 15:52:43 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Función para limpiar la memoria de los argumentos
static void clean_up_echo(char **arr)
{
    int i;

    i = 0;
    if (arr)
    {
        while (arr[i])
        {
            free(arr[i]);
            i++;
        }
        free(arr);
    }
}

static char *remove_quotes(char *str)
{
    int len = ft_strlen(str);
    if ((str[0] == '\'' && str[len - 1] == '\'') || 
        (str[0] == '"' && str[len - 1] == '"'))
    {
        str[len - 1] = '\0';   // Eliminar la última comilla
        return (str + 1);      // Mover el puntero para ignorar la primera comilla
    }
    return str;
}

// Verifica si el argumento es la opción -n
int is_n_option(char *str)
{
    int i;

    i = 1;
    if (str[0] == '-')
    {
        while (str[i] == 'n')
            i++;
        if (str[i] == '\0' && i != 1)
            return (1);
    }
    return (0);
}

// Función para analizar los argumentos de la línea de comandos
static char **parse_arguments(char *command)
{
    char    **args;
    char    *current_arg;
    size_t  arg_len;
    int     in_single_quotes;
    int     in_double_quotes;
    int     i;
    int     j;

    args = malloc(sizeof(char *) * (ft_strlen(command) / 2 + 2)); // Asignar espacio suficiente
    if (!args)
        return (NULL);

    in_single_quotes = 0;
    in_double_quotes = 0;
    i = 0;
    j = 0;
    current_arg = ft_calloc(1, 1); // Inicializar el argumento actual

    if (!current_arg)
    {
        free(args);
        return (NULL);
    }

    while (command[i])
    {
        if (command[i] == '\'' && !in_double_quotes)
            in_single_quotes = !in_single_quotes;
        else if (command[i] == '"' && !in_single_quotes)
            in_double_quotes = !in_double_quotes;
        else if (command[i] == ' ' && !in_single_quotes && !in_double_quotes)
        {
            if (ft_strlen(current_arg) > 0)
            {
                args[j++] = current_arg;
                current_arg = ft_calloc(1, 1);
                if (!current_arg)
                {
                    clean_up_echo(args);
                    return (NULL);
                }
            }
        }
        else
        {
            arg_len = ft_strlen(current_arg);
            current_arg = simple_realloc(current_arg, arg_len + 2, arg_len + 2);
            if (!current_arg)
            {
                clean_up_echo(args);
                return (NULL);
            }
            current_arg[arg_len] = command[i];
            current_arg[arg_len + 1] = '\0';
        }
        i++;
    }

    if (ft_strlen(current_arg) > 0)
        args[j++] = current_arg;
    args[j] = NULL;
    return (args);
}

// Función para imprimir las partes del echo
static void print_echo_parts(char **str, int start_index)
{
    int first;
    int i;

    first = 1;
    i = start_index;
    while (str[i])
    {
        if (!first)
            write(STDOUT_FILENO, " ", 1);
        ft_putstr_fd(str[i], STDOUT_FILENO);
        first = 0;
        i++;
    }
}

// Función principal de echo
void ft_echo(char *command)
{
    char    **str;
    int     i;
    int     n_option;

    i = 0;
    n_option = 0;

    // Eliminar espacios alrededor del comando
    char *trimmed_command = remove_front_and_back_spaces(command);

    // Eliminar comillas alrededor del comando
    trimmed_command = remove_quotes(trimmed_command);

    // Si el comando es "echo" solo, imprimir una nueva línea
    if (ft_strcmp(trimmed_command, "echo") == 0)
    {
        printf("\n");
        return;
    }

    str = parse_arguments(trimmed_command + 5); // Parsear correctamente los argumentos
    if (!str)
    {
        manage_error(200, 0);
        return;
    }

    // Verifica la opción -n
    if (str[0] && is_n_option(str[i]))
    {
        while (str[i] && is_n_option(str[i]))
        {
            n_option = 1;
            i++;
        }
    }

    if (str)
        print_echo_parts(str, i);

    // Añadir nueva línea si no está habilitada la opción -n
    if (!n_option)
        write(STDOUT_FILENO, "\n", 1);

    clean_up_echo(str);
    manage_error(0, 0);
    return;
}