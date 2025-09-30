# Adventure Game Makefile

NAME = adventure

# Source files
SRCS = main.c game.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# MinilibX settings for macOS
MLX_DIR = ./minilibx

# Use the macOS version of minilibX
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Add minilibx directory to include path
INCLUDES = -I. -I$(MLX_DIR)

# Include directories
INCLUDES = -I.

# Default target
all: $(NAME)

# Build the executable
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

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
