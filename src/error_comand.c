/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:05:02 by manufern          #+#    #+#             */
/*   Updated: 2024/08/20 12:18:23 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

 int check_quotes(char *command)
{
    int i;
    int quotes_2 = 0;
    int quotes_1 = 0;

    i = 0;
    while (command[i] != '\0')
    {
        if (command[i] == '"')
        {
            quotes_2++;
        }
        else if (command[i] == '\'')
        {
            quotes_1++;
        }
        i++;
    }

    if (quotes_2 % 2 == 0 && quotes_1 % 2 == 0)
        return 1;
    else
        return (manage_error(200, 0), 0);
}

int check_special_chars(char *line)
{
    int prev_char_was_special = 0;

    while (*line)
    {
        if (*line == '|')
        {
            if (prev_char_was_special)
                return 0;
            prev_char_was_special = 1;
        }
        else
        {
            prev_char_was_special = 0;
        }
        line++;
    }
    return 1;
}

int check_redirections(char *line)
{
    while (*line)
    {
        if (*line == '>' || *line == '<')
        {
            if (*(line + 1) == *line)
                line++;
            while (isspace(*(line + 1)))
                line++;
            
            if (*(line + 1) == '\0')
                return 0;
        }
        line++;
    }
    return 1;
}

int check_syntax(char *line)
{
    while (isspace(*line))
        line++;
    if (*line == '|')
        return 0;
    char *end = line + strlen(line) - 1;
    while (end > line && isspace(*end))
        end--;
    
    if (*end == '|')
        return 0;

    return 1;
}

// Valida los argumentos para detectar errores como 'ls ""'
int all_isspace(char *start, char *end)
{
    while (start < end)
    {
        if (!isspace(*start))
            return 0;
        start++;
    }
    return 1;
}

int has_space(char *start, char *end)
{
    while (start < end)
    {
        if (isspace(*start))
            return 1;
        start++;
    }
    return 0;
}

int validate_arguments(char *line)
{
    char *start = line;
    /* char *end; */
    /* int inside_quotes = 0; */ // 0: no en comillas, 1: en comillas dobles, 2: en comillas simples

    while (*start)
    {
        // Saltar espacios y tabulaciones
        while (isspace(*start))
            start++;

        if (*start == '\0')
            break;

        /* end = start; */

        // Manejo de comillas simples y dobles
        if (*start == '"' || *start == '\'')
        {
            char quote_char = *start;
            start++;  // Avanza para empezar a analizar el contenido dentro de las comillas

            // Busca el final de las comillas
            while (*start && *start != quote_char)
            {
                start++;
            }

            // Verifica si se encontró el final de las comillas
            if (*start != quote_char)
            {
                printf("error por aqui\n");
                return 0;  // Error: comillas no balanceadas
            }

            start++;  // Avanza más allá de la comilla de cierre
        }
        else
        {
            // Encuentra el fin del argumento
            while (*start && !isspace(*start) && *start != '"' && *start != '\'')
                start++;
        }

        // Avanza al siguiente argumento
        /* end = start; */
    }

    return 1;  // Todos los argumentos son válidos
}

// Manejo de errores
void exit_with_error(const char *message)
{
    write(2, message, strlen(message));
}

char *remove_spaces(const char *str)
{
    if (str == NULL)
        return NULL;

    // Contar el tamaño del nuevo string sin espacios
    size_t length = strlen(str);
    size_t i, j = 0;

    // Alocar memoria para el nuevo string
    char *result = malloc(length + 1);  // +1 para el carácter de terminación '\0'
    if (result == NULL)
        return NULL;

    // Copiar solo los caracteres que no son espacios
    for (i = 0; i < length; i++)
    {
        if (str[i] != ' ')
        {
            result[j++] = str[i];
        }
    }

    // Añadir el carácter de terminación al final del nuevo string
    result[j] = '\0';

    return result;
}

int ft_parsing(char *line)
{
    char *aux;

    aux = line;
    if (!line || !*line)
    {
        exit_with_error("empty command line\n");
        return 1;
    }

    if (ft_strstr(line, "echo"))
        return (0);
    if(line != NULL)
    {
        aux = remove_spaces(aux);
        if(ft_strncmp(aux, "\"<\"", 3) == 0 || ft_strncmp(aux, "\">\"", 3) == 0 || ft_strncmp(aux, "\">>\"", 4) == 0 || ft_strncmp(aux, "\"<<\"", 4) == 0)
        {
            exit_with_error("command not found\n");
            free(aux);
            return 1;
        }
        free(aux);
        
    }
    if (check_quotes(line) == 0)
    {
        exit_with_error("quotes error\n");
        return 1;
    }

    if (check_special_chars(line) == 0)
    {
        exit_with_error("special chars error\n");
        return 1;
    }

    if (check_redirections(line) == 0)
    {
        exit_with_error("redirection syntax error\n");
        return 1;
    }

    if (check_syntax(line) == 0)
    {
        exit_with_error("general syntax error\n");
        return 1;
    }

    if (validate_arguments(line) == 0)
    {
        exit_with_error("invalid argument error\n");
        return 1;
    }

    return 0; // Devuelve 0 si todo está correcto
}