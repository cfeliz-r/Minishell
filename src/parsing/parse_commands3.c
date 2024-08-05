/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:57:31 by manufern          #+#    #+#             */
/*   Updated: 2024/08/05 16:29:52 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Maneja las comillas simples y dobles en el contexto de un comando.
static void handle_quotes(char c, size_t *in_single_quotes, size_t *in_double_quotes)
{
    // Si se encuentra una comilla doble y no estamos dentro de comillas simples,
    // alterna el estado de in_double_quotes (activa o desactiva).
    if (c == '"' && !*in_single_quotes)
        *in_double_quotes = !*in_double_quotes;
    // Si se encuentra una comilla simple y no estamos dentro de comillas dobles,
    // alterna el estado de in_single_quotes (activa o desactiva).
    else if (c == '\'' && !*in_double_quotes)
        *in_single_quotes = !*in_single_quotes;
}

// Añade un carácter a la cadena resultante y ajusta el tamaño del búfer si es necesario.
static char *append_char(char *result, char c, size_t *j, size_t *buffer_size)
{
    size_t  old_buffer_size;   // Variable para almacenar el tamaño anterior del búfer.
    char    *new_result;       // Puntero para el nuevo búfer en caso de que sea necesario redimensionar.

    // Si el índice actual ha alcanzado el tamaño del búfer menos 1,
    // es necesario redimensionar el búfer para añadir más caracteres.
    if (*j >= *buffer_size - 1)
    {
        old_buffer_size = *buffer_size;   // Guarda el tamaño actual del búfer.
        *buffer_size *= 2;                // Duplica el tamaño del búfer.
        // Realiza la reubicación de memoria para ajustar el tamaño del búfer.
        new_result = simple_realloc(result, old_buffer_size, *buffer_size);
        if (!new_result)
            return (free(result), NULL);  // Si falla la reubicación, libera la memoria original y retorna NULL.
        result = new_result;              // Actualiza el puntero resultante al nuevo búfer.
    }
    result[(*j)++] = c;   // Añade el carácter al resultado y avanza el índice j.
    return (result);      // Retorna la cadena resultante actualizada.
}

// Maneja las secuencias de escape dentro del comando.
static char *handle_escape_sequence(const char *command, t_parse_context *ctx)
{
    // Añade el carácter de escape a la cadena resultante.
    ctx->result = append_char(ctx->result, command[(ctx->i)++],
                              &(ctx->j), &(ctx->buffer_size));
    if (!ctx->result)
        return (NULL);  // Si falla, retorna NULL.

    // Añade el siguiente carácter después de la secuencia de escape a la cadena resultante.
    ctx->result = append_char(ctx->result, command[(ctx->i)++],
                              &(ctx->j), &(ctx->buffer_size));
    return (ctx->result);  // Retorna la cadena resultante actualizada.
}

// Maneja la expansión de variables de entorno en el comando.
static char *handle_variable_expansion(const char *command,
                                       t_parse_context *ctx, t_list_env *envp)
{
    char    key[256];  // Almacena el nombre de la variable.
    size_t  k;         // Índice para recorrer el nombre de la variable.
    char    *value;    // Puntero al valor de la variable de entorno.

    k = 0;
    // Extrae el nombre de la variable del comando mientras sea alfanumérica o un guion bajo.
    while (command[ctx->i] && (ft_isalnum(command[ctx->i])
           || command[ctx->i] == '_') && k < sizeof(key) - 1)
        key[k++] = command[(ctx->i)++];
    key[k] = '\0';  // Termina la cadena con un carácter nulo.

    // Busca el valor de la variable en el entorno.
    value = find_env_value(envp, key);
    while (value && *value)
    {
        // Añade el valor de la variable al resultado.
        ctx->result = append_char(ctx->result, *value++, &(ctx->j),
                                  &(ctx->buffer_size));
        if (!ctx->result)
            return (NULL);  // Si falla, retorna NULL.
    }
    return (ctx->result);  // Retorna la cadena resultante actualizada.
}

// Procesa un carácter del comando según su contexto.
static char *process_char(const char *command, t_parse_context *ctx,
                          t_list_env *envp)
{
    // Si el carácter es una comilla simple o doble, maneja el cambio de estado de las comillas.
    if (command[ctx->i] == '"' || command[ctx->i] == '\'')
        handle_quotes(command[(ctx->i)++], &(ctx->in_single_quotes),
                      &(ctx->in_double_quotes));
    // Si el carácter es una barra invertida (\), maneja la secuencia de escape.
    else if (command[ctx->i] == '\\')
        ctx->result = handle_escape_sequence(command, ctx);
    // Si el carácter es un punto y coma (;) y no estamos dentro de comillas,
    // lo añade al resultado.
    else if (command[ctx->i] == ';' && !ctx->in_single_quotes
             && !ctx->in_double_quotes)
        ctx->result = append_char(ctx->result, command[(ctx->i)++],
                                  &(ctx->j), &(ctx->buffer_size));
    // Si el carácter es un signo de dólar ($) y estamos dentro de comillas dobles,
    // maneja la expansión de variables.
    else if (command[ctx->i] == '$' && ctx->in_double_quotes)
    {
        (ctx->i)++;  // Avanza el índice para saltar el signo de dólar.
        ctx->result = handle_variable_expansion(command, ctx, envp);
    }
    // Para cualquier otro carácter, simplemente lo añade al resultado.
    else
        ctx->result = append_char(ctx->result, command[(ctx->i)++],
                                  &(ctx->j), &(ctx->buffer_size));
    return (ctx->result);  // Retorna la cadena resultante actualizada.
}

// Interpreta el comando, manejando comillas, secuencias de escape y expansiones de variables.
char *interpret_command(const char *command, t_list_env *envp)
{
    t_parse_context ctx;  // Contexto de parsing para almacenar el estado durante la interpretación.

    ctx.i = 0;  // Inicializa el índice de la cadena original.
    ctx.j = 0;  // Inicializa el índice de la cadena resultante.
    ctx.in_single_quotes = 0;  // Estado inicial de comillas simples (desactivado).
    ctx.in_double_quotes = 0;  // Estado inicial de comillas dobles (desactivado).
    ctx.buffer_size = ft_strlen(command) * 2 + 1;  // Calcula el tamaño inicial del búfer.
    ctx.result = malloc(ctx.buffer_size);  // Reserva memoria para la cadena resultante.
    if (!ctx.result)
        return (NULL);  // Si falla la reserva de memoria, retorna NULL.

    // Recorre el comando carácter por carácter hasta el final.
    while (command[ctx.i] != '\0')
    {
        ctx.result = process_char(command, &ctx, envp);  // Procesa cada carácter del comando.
        if (!ctx.result)
            return (NULL);  // Si falla el procesamiento, retorna NULL.
    }

    // Si al final del comando quedan comillas abiertas, libera la memoria y retorna NULL.
    if (ctx.in_double_quotes || ctx.in_single_quotes)
        return (free(ctx.result), NULL);

    ctx.result[ctx.j] = '\0';  // Añade el carácter nulo al final de la cadena resultante.
    return (ctx.result);  // Retorna la cadena resultante que representa el comando interpretado.
}

