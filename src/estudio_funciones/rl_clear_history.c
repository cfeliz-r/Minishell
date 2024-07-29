#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
//Esta funcion se utiliza para borrar el historial de comandos.
int main()
{
    char *comand;
    int i = 0;
    
    while (1)
    {
    comand = readline("MINISHELL ➤ ");
    if (strlen(comand) > 0)
    {
      add_history(comand);
      i ++;
    }
    printf("comando: %s\n", comand);
    if (i == 3)
    {
      rl_clear_history(); //Funcion utilizada para borrar el historyal de comandos
      i = 0;
    }
    free(comand);
    }
    exit (0);
}
