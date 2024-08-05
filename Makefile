# --------------------------------------
# Nombre del archivo ejecutable
# --------------------------------------
NAME = minishell

# --------------------------------------
# Directorio de archivos objeto
# --------------------------------------
OBJDIR = obj

# --------------------------------------
# Archivos fuente
# --------------------------------------
SRC = src/minishell.c \
      src/building/ft_echo.c \
      src/building/ft_pwd.c \
      src/building/ft_env.c \
      src/building/ft_cd.c \
      src/utils/utils.c \
      src/commands/check_and_path.c \
      src/commands/exec_command.c \
	  src/parsing/parse_commands.c \
      src/parsing/parse_commands2.c \
      src/signals/signals.c \
      src/list_files/lists.c \
	  src/redirection/redirections.c

# --------------------------------------
# Archivos objeto
# --------------------------------------
OBJ = $(SRC:src/%.c=$(OBJDIR)/%.o)

# --------------------------------------
# Compilador y opciones
# --------------------------------------
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address,undefined,leak
LIBS = -lreadline

# --------------------------------------
# Directorio y archivo de la librería libft
# --------------------------------------
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# --------------------------------------
# Colores y estilos
# --------------------------------------
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m

# --------------------------------------
# Regla por defecto
# --------------------------------------
all: $(NAME)

# --------------------------------------
# Regla para compilar el archivo ejecutable
# --------------------------------------
$(NAME): $(OBJ) $(LIBFT)
	@echo "$(BLUE)Construyendo el hábitat de los babuinos... $(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS) -L$(LIBFT_DIR) -lft \
		&& echo "$(GREEN)¡Hábitat de los babuinos construido con éxito!$(RESET)" \
		|| echo "$(RED)Error en la construcción del hábitat$(RESET)"

# --------------------------------------
# Regla para compilar archivos .c en archivos .o
# --------------------------------------
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@) # Asegúrate de que el directorio necesario exista
	@echo "$(MAGENTA)Compilando $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# --------------------------------------
# Regla para construir la librería libft
# --------------------------------------
$(LIBFT):
	@echo "$(YELLOW)Cultivando el árbol de bananas (librería libft)... $(RESET)"
	@make -C $(LIBFT_DIR)

# --------------------------------------
# Regla para limpiar el hábitat de los babuinos
# --------------------------------------
clean:
	@echo "$(RED)Desmantelando el hábitat de los babuinos... $(RESET)"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean

# --------------------------------------
# Regla para eliminar el hábitat y la librería
# --------------------------------------
fclean: clean
	@echo "$(RED)Destruyendo el hábitat y el árbol de bananas... $(RESET)"
	@rm -f $(NAME)
	@rm -f $(LIBFT)

# --------------------------------------
# Regla para reconstruir el hábitat desde cero
# --------------------------------------
re: fclean all

# --------------------------------------
# Declaración de objetivos que no son archivos
# --------------------------------------
.PHONY: all clean fclean re
