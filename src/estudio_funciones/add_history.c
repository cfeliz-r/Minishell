#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
// Esta función almacena los comandos ingresados por el usuario en un historial,
// permitiendo luego acceder a estos comandos utilizando las flechas del teclado.
// Es útil para mejorar la experiencia del usuario al interactuar con una línea de comandos,
// proporcionando una forma conveniente de recuperar y reutilizar comandos anteriores.
int main()
{
    char *comand;
    
    while (1)
    {
    comand = readline("MINISHELL ➤ ");
    if (strlen(comand) > 0)
      add_history(comand);// Esta función almacena los comandos ingresados por el usuario en un historial
    printf("comando: %s\n", comand);
    free(comand);
    }
    exit (0);
}
