# Nombre del archivo ejecutable
NAME = minishell

# Nombre del archivo fuente
SRC =	src/minishell.c \
		src/building/ft_echo.c \
		src/building/ft_pwd.c \
		src/building/ft_env.c \
		src/building/ft_cd.c \
		src/utils.c \
		src/check_and_path.c \
		src/exec_command.c \
		src/parse_commands.c 

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address,undefined,leak
# Llamada a readline
LIBS = -lreadline

# Directorio de la librería libft
LIBFT_DIR = ./libft

# Archivo de la librería libft
LIBFT = $(LIBFT_DIR)/libft.a

# Regla para compilar el ejecutable
all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(LIBS) -L$(LIBFT_DIR) -lft

$(LIBFT):
	make -C $(LIBFT_DIR)

# Regla para limpiar archivos generados
clean:
	rm -f $(NAME)
	make -C $(LIBFT_DIR) clean

# Regla para limpiar y eliminar archivos generados
fclean: clean
	rm -f $(LIBFT)
	make -C $(LIBFT_DIR) fclean

# Regla para recompilar todo
re: fclean all

.PHONY: all clean fclean re
