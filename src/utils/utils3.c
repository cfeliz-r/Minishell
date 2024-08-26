/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:56:03 by manufern          #+#    #+#             */
/*   Updated: 2024/08/26 19:04:17 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to determine if a position is inside quotes
int is_within_quotes(const char* text, int index) {
    int in_quotes = 0;
    int i = 0;

    while (i <= index) {
        if (text[i] == '"' || text[i] == '\'') {
            in_quotes = !in_quotes;
        }
        i++;
    }

    return in_quotes;
}

// Function to search for a string outside of quotes
int search_string_outside_quotes(const char* text, const char* search) {
    int text_len = strlen(text);
    int search_len = strlen(search);
    int in_quotes = 0;
    int i = 0;

    while (i <= text_len - search_len) {
        // Toggle the in_quotes flag when encountering quotes
        if (text[i] == '"' || text[i] == '\'') {
            in_quotes = !in_quotes;
        }

        // Check if the substring matches the search string
        if (!in_quotes && strncmp(&text[i], search, search_len) == 0) {
            // Verify that the match is not within quotes
            if (i == 0 || !is_within_quotes(text, i - 1)) {
                if (i + search_len == text_len || !is_within_quotes(text, i + search_len - 1)) {
                    return 1; // Found outside of quotes
                }
            }
        }

        i++;
    }

    return 0; // Not found outside of quotes
}