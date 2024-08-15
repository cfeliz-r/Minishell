/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:27:25 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/08/15 13:08:33 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char *join_paths(char *dir, char *cmd)
{
    char *full_path;
    char *result;

    // Concatenar directorio y comando con '/'
    full_path = ft_strjoin(dir, "/");
    result = ft_strjoin(full_path, cmd);
    free(full_path);
    return (result);
}

// Función para obtener rutas del PATH en el entorno
static char **get_paths(t_list_env *envp)
{
    t_list_env *aux;
    char **paths;

    aux = envp;
    while (aux && ft_strnstr(aux->envp_content, "PATH=", 5) == 0)
        aux = aux->next;
    if (!aux)
        return (NULL);

    // Separar las rutas del PATH por ':'
    paths = ft_split(aux->envp_content + 5, ':');
    return (paths);
}

// Función para buscar en las rutas posibles
static char *search_paths(char **paths, char *cmd)
{
    char *res;
    int i;

    i = 0;
    while (paths[i])
    {
        // Construir el path completo para el comando
        res = join_paths(paths[i], cmd);
        // Verificar si el archivo existe y es ejecutable
        if (access(res, F_OK | X_OK) == 0)
        {
            clean_up(paths, NULL, 0);
            return (res);
        }
        free(res);
        i++;
    }
    clean_up(paths, NULL, 0);
    return (NULL);
}

// Función para encontrar la ruta del comando y retornar el comando limpio
char *find_command_path(char *cmd, t_list_env *envp)
{
    char **paths;
    char *res;
    char *clean_cmd;

    if (cmd == NULL)
        return (NULL);

    // Eliminar comillas si están presentes
    clean_cmd = ft_strdup(cmd);
    if (clean_cmd[0] == '"' && clean_cmd[strlen(clean_cmd) - 1] == '"')
    {
        clean_cmd[strlen(clean_cmd) - 1] = '\0';
        memmove(clean_cmd, clean_cmd + 1, strlen(clean_cmd)); // Eliminar primer carácter (comilla)
    }
    else if (clean_cmd[0] == '\'' && clean_cmd[strlen(clean_cmd) - 1] == '\'')
    {
        clean_cmd[strlen(clean_cmd) - 1] = '\0';
        ft_memmove(clean_cmd, clean_cmd + 1, ft_strlen(clean_cmd)); // Eliminar primer carácter (comilla)
    }

    // Comandos integrados (built-ins)
    if (ft_strncmp(clean_cmd, "cd ", 3) == 0 || ft_strcmp(clean_cmd, "cd") == 0 || 
        ft_strncmp(clean_cmd, "echo ", 5) == 0 || ft_strcmp(clean_cmd, "echo") == 0 || 
        ft_strncmp(clean_cmd, "env ", 4) == 0 || ft_strcmp(clean_cmd, "env") == 0 || 
        ft_strncmp(clean_cmd, "pwd ", 4) == 0 || ft_strcmp(clean_cmd, "pwd") == 0 || 
        ft_strncmp(clean_cmd, "export ", 7) == 0 || ft_strcmp(clean_cmd, "export") == 0 || 
        ft_strncmp(clean_cmd, "unset ", 6) == 0 || ft_strcmp(clean_cmd, "unset") == 0)
    {
        return (clean_cmd); // Retornar el comando limpio sin comillas
    }
    
    // Verificar comandos absolutos o relativos
    if (clean_cmd[0] == '/' || ft_strncmp(clean_cmd, "./", 2) == 0)
    {
        if (access(clean_cmd, F_OK | X_OK) == 0)
            return (clean_cmd);
        else
        {
            free(clean_cmd);
            return (NULL);
        }
    }

    // Obtener rutas del PATH y buscar el comando
    paths = get_paths(envp);
    if (paths == NULL)
    {
        free(clean_cmd);
        return (NULL);
    }
    res = search_paths(paths, clean_cmd);
    free(clean_cmd);
    return (res);
}
