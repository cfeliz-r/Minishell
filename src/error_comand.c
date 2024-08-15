/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:05:02 by manufern          #+#    #+#             */
/*   Updated: 2024/08/14 15:33:51 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Verifica si las comillas están balanceadas
 int check_quotes(char *command)
{
	int i;
	int quotes_2;
	int quotes_1;

	i = 0;
	quotes_2 = 0;
	quotes_1 = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '"')
		{
			quotes_2++;
			i++;
			while (command[i] != '"' && command[i] != '\0')
				i++;
			if (command[i] == '"')
			{
				quotes_2++;
				i++;
			}
		}
		else if (command[i] == '\'')
		{
			quotes_1++;
			i++;
			while (command[i] != '\'' && command[i] != '\0')
				i++;
			if (command[i] == '\'')
			{
				quotes_1++;
				i++;
			}
		}
		else
			i++;
	}
	if (quotes_2 % 2 == 0 && quotes_1 % 2 == 0)
		return 1;
	else
		return (manage_error(200, 0), 0);
}

// Verifica si los caracteres especiales están bien colocados
int check_special_chars(char *line)
{
    int prev_char_was_special = 0;

    while (*line)
    {
        if (*line == '|')
        {
            if (prev_char_was_special)
                return 0; // Dos caracteres especiales seguidos
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

// Verifica si las redirecciones están bien formateadas
int check_redirections(char *line)
{
    while (*line)
    {
        if (*line == '>' || *line == '<')
        {
            if (*(line + 1) == *line) // Maneja `>>` o `<<`
                line++;
            
            // Verifica si la redirección está seguida por un espacio o fin de línea
            while (isspace(*(line + 1)))
                line++;
            
            if (*(line + 1) == '\0')
                return 0; // Redirección sin destino
        }
        line++;
    }
    return 1;
}

// Verifica la sintaxis general
int check_syntax(char *line)
{
    while (isspace(*line))
        line++;
    
    // Verifica si la línea comienza con un carácter especial
    if (*line == '|')
        return 0;

    // Verifica que la línea no termine con un carácter especial no permitido
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

// Valida los argumentos para detectar errores como 'ls " "'
int validate_arguments(char *line)
{
    char *start = line;
    char *end;
    int inside_quotes = 0; // 0: no en comillas, 1: en comillas dobles, 2: en comillas simples

    // Comando especial 'echo' para ser manejado sin errores

    while (*start)
    {
        // Saltar espacios y tabulaciones
        while (isspace(*start))
            start++;
        
        if (*start == '\0')
            break;

        end = start;
        if (*start == '"')
        {
            // Manejo de comillas dobles
            inside_quotes = 1;
            end++;  // Avanzar más allá de la primera comilla
            while (*end && (inside_quotes || *end != '"'))
            {
                if (*end == '"')
                    inside_quotes = !inside_quotes; // Toggle inside_quotes flag
                end++;
            }
            if (*end == '"')
                end++; // Avanzar más allá de la última comilla

            // Verificar si hay espacios dentro de las comillas dobles
            if (has_space(start + 1, end - 1))
                return 0; // Error: espacios dentro de comillas dobles
        }
        else if (*start == '\'')
        {
            // Manejo de comillas simples
            inside_quotes = 2; // Diferente flag para comillas simples
            end++;  // Avanzar más allá de la primera comilla simple
            while (*end && (inside_quotes == 2 || *end != '\''))
            {
                if (*end == '\'')
                    inside_quotes = 0; // Toggle inside_quotes flag
                end++;
            }
            if (*end == '\'')
                end++; // Avanzar más allá de la última comilla simple

            // Verificar si hay espacios dentro de las comillas simples
            if (has_space(start + 1, end - 1))
                return 0; // Error: espacios dentro de comillas simples
        }
        else
        {
            // Encuentra el fin del argumento
            while (*end && !isspace(*end) && *end != '"' && *end != '\'')
                end++;
        }

        // Mover al siguiente token
        start = end; 
    }

    // Verificar que todas las comillas estén cerradas
    if (inside_quotes)
        return 0;  // Cita no cerrada detectada

    return 1; // Todos los argumentos son válidos
}


// Manejo de errores
void exit_with_error(const char *message)
{
    write(2, message, ft_strlen(message));
}

int ft_parsing(char *line)
{
    if (!line || !*line)
    {
        exit_with_error("empty command line\n");
        return 1;
    }

    if (ft_strstr(line, "echo"))
        return (0);
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
