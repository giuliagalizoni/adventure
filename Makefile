# Adventure Game Makefile

NAME = adventure

# Directories
SRC_DIR = src
INC_DIR = includes
OBJ_DIR = obj
MLX_DIR = minilibx
ASSETS_DIR = assets

# Source files (without directory prefix)
SRCS = main.c game.c levels.c player.c rendering.c sprites.c

# Add directory prefix to source files
SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRCS))

# Object files in obj directory
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# MinilibX settings for macOS
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Include directories
INCLUDES = -I$(INC_DIR) -I$(MLX_DIR)

# Default target
all: $(OBJ_DIR) $(NAME)

# Create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build the executable
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

# Compile source files from src/ to obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Run the game
run: $(NAME)
	./$(NAME)

# Install minilibX (if needed)
install_mlx:
	@echo "Installing minilibX..."
	@echo "Please make sure you have minilibX installed in /usr/local/lib"
	@echo "You can download it from: https://github.com/42Paris/minilibx-linux"

.PHONY: all clean fclean re run install_mlx
