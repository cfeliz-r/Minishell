#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
// La función readline se compila con las banderas -lreadline y -lhistory para enlazar las bibliotecas Readline y History.
// La función readline proporciona una interfaz interactiva para leer la entrada del usuario desde la consola, permitiendo edición y navegación en la línea de texto.
// Uso típico de la función: readline("prompt") - muestra el mensaje "prompt" y devuelve una línea de texto ingresada por el usuario.
int main()
{
    char *comand;
    
    while (1) //El bucle al usar "readline" se usa para dejar al uusuario entro de la minishell y n o sacarle cada vez que escribe un comando
    {
    comand = readline("MINISHELL ➤ ");
    printf("comando: %s\n", comand);
    }
    exit (0);
}
