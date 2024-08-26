/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:56:03 by manufern          #+#    #+#             */
/*   Updated: 2024/08/26 19:01:28 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Función para determinar si una posición está dentro de comillas
int esta_dentro_de_comillas(const char* texto, int indice) {
    int dentro_comillas = 0;
    for (int i = 0; i <= indice; i++) {
        if (texto[i] == '"' || texto[i] == '\'') {
            dentro_comillas = !dentro_comillas;
        }
    }
    return dentro_comillas;
}

// Función para buscar una cadena fuera de comillas
int buscar_cadena_fuera_de_comillas(const char* texto, const char* cadena) {
    int len_texto = strlen(texto);
    int len_cadena = strlen(cadena);
    int dentro_comillas = 0;

    for (int i = 0; i <= len_texto - len_cadena; i++) {
        // Cambia el estado de dentro_comillas si se encuentra una comilla
        if (texto[i] == '"' || texto[i] == '\'') {
            dentro_comillas = !dentro_comillas;
        }

        // Verifica si la subcadena coincide con la cadena buscada
        if (!dentro_comillas && strncmp(&texto[i], cadena, len_cadena) == 0) {
            // Verifica que la coincidencia no está entre comillas
            if (i == 0 || !esta_dentro_de_comillas(texto, i - 1)) {
                if (i + len_cadena == len_texto || !esta_dentro_de_comillas(texto, i + len_cadena - 1)) {
                    return 1; // Encontrado fuera de comillas
                }
            }
        }
    }

    return 0; // No encontrado fuera de comillas
}