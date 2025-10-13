#include "adventure.h"
#include <stdio.h>
#include <string.h>

// Initialize all levels with themed maps
int	init_levels(t_game *game)
{
	// London - Collect pints of cider 🍺
	game->levels[LONDON].name = "London";
	game->levels[LONDON].collectible_name = "Pints of Cider";
	game->levels[LONDON].width = 15;
	game->levels[LONDON].height = 10;
	game->levels[LONDON].total_collectibles = 3;
	game->levels[LONDON].collected = 0;

	// Simple London map (you can customize this!)
	static char london_map[10][16] = {
		"111111111111111",
		"1P000C0000000E1",
		"1011110111101011",
		"100000000000001",
		"1011M01110110111",
		"100000C000000001",
		"1011101111011011",
		"100000000000001",
		"101110C111101111",
		"111111111111111"
	};

	// Paris - Collect croissants 🥐
	game->levels[PARIS].name = "Paris";
	game->levels[PARIS].collectible_name = "Croissants";
	game->levels[PARIS].width = 15;
	game->levels[PARIS].height = 10;
	game->levels[PARIS].total_collectibles = 4;
	game->levels[PARIS].collected = 0;

	static char paris_map[10][16] = {
		"111111111111111",
		"1P00C00000C000E1",
		"1011101111110111",
		"1000000000000001",
		"111010M010101111",
		"100000000000C001",
		"1011101111110111",
		"100000C000000001",
		"1011111111111011",
		"111111111111111"
	};

	// Rome - Collect gelatos 🍨
	game->levels[ROME].name = "Rome";
	game->levels[ROME].collectible_name = "Gelatos";
	game->levels[ROME].width = 15;
	game->levels[ROME].height = 10;
	game->levels[ROME].total_collectibles = 5;
	game->levels[ROME].collected = 0;

	static char rome_map[10][16] = {
		"111111111111111",
		"1P0C000C000C00E1",
		"1011011101110111",
		"100000000000001",
		"1110M01110101111",
		"1C0000000000C001",
		"1011101111101111",
		"100000000000001",
		"111111111111111",
		"111111111111111"
	};

	// Berlin - collect döner �
	game->levels[BERLIN].name = "Berlin";
	game->levels[BERLIN].collectible_name = "Döner";
	game->levels[BERLIN].width = 15;
	game->levels[BERLIN].height = 10;
	game->levels[BERLIN].total_collectibles = 6;
	game->levels[BERLIN].collected = 0;

	static char berlin_map[10][16] = {
		"111111111111111",
		"1P0C0C000C0C00E1",
		"1011101110111011",
		"100000000000001",
		"111010M010101111",
		"1C000000000000C1",
		"1011101111110111",
		"100000C000C0001",
		"111111111111111",
		"111111111111111"
	};

	// Amsterdam - Final level, collect stroopwafels 🧇
	game->levels[AMSTERDAM].name = "Amsterdam";
	game->levels[AMSTERDAM].collectible_name = "Stroopwafels";
	game->levels[AMSTERDAM].width = 15;
	game->levels[AMSTERDAM].height = 10;
	game->levels[AMSTERDAM].total_collectibles = 7;
	game->levels[AMSTERDAM].collected = 0;

	static char amsterdam_map[10][16] = {
		"111111111111111",
		"1P0C0C0C00C0C0E1",
		"1011101011101111",
		"1000000000000001",
		"101110M011101011",
		"1C0000000000C001",
		"1011101111011011",
		"10000C000C00001",
		"111111111111111",
		"111111111111111"
	};

	// Allocate memory for maps and copy data
	for (int level = 0; level < MAX_CITIES; level++)
	{
		game->levels[level].map = malloc(sizeof(char *) * game->levels[level].height);
		if (!game->levels[level].map)
		{
			// Clean up previously allocated memory
			for (int cleanup = 0; cleanup < level; cleanup++)
			{
				for (int j = 0; j < game->levels[cleanup].height; j++)
					free(game->levels[cleanup].map[j]);
				free(game->levels[cleanup].map);
			}
			return (0);
		}

		for (int i = 0; i < game->levels[level].height; i++)
		{
			game->levels[level].map[i] = malloc(sizeof(char) * (game->levels[level].width + 1));
			if (!game->levels[level].map[i])
			{
				// Clean up this level's partial allocation
				for (int cleanup_i = 0; cleanup_i < i; cleanup_i++)
					free(game->levels[level].map[cleanup_i]);
				free(game->levels[level].map);
				// Clean up previous levels
				for (int cleanup = 0; cleanup < level; cleanup++)
				{
					for (int j = 0; j < game->levels[cleanup].height; j++)
						free(game->levels[cleanup].map[j]);
					free(game->levels[cleanup].map);
				}
				return (0);
			}

			// Copy the appropriate map
			if (level == LONDON)
			{
				strncpy(game->levels[level].map[i], london_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
			else if (level == PARIS)
			{
				strncpy(game->levels[level].map[i], paris_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
			else if (level == ROME)
			{
				strncpy(game->levels[level].map[i], rome_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
			else if (level == BERLIN)
			{
				strncpy(game->levels[level].map[i], berlin_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
			else if (level == AMSTERDAM)
			{
				strncpy(game->levels[level].map[i], amsterdam_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
		}
	}

	return (1);
}

// Load all game sprites
int	load_sprites(t_game *game)
{
	if (!game || !game->mlx)
		return (0);

	// Initialize all sprite pointers to NULL first
	game->sprites.player_front = NULL;
	game->sprites.moka = NULL;
	game->sprites.cider = NULL;
	game->sprites.croissant = NULL;
	game->sprites.gelato = NULL;
	game->sprites.doner = NULL;
	game->sprites.stroopwafel = NULL;
	game->sprites.wall = NULL;
	game->sprites.floor = NULL;
	game->sprites.exit = NULL;

	// Load player sprite
	int width, height;
	game->sprites.player_front = mlx_xpm_file_to_image(game->mlx,
		"assets/player_front.xpm", &width, &height);
	if (!game->sprites.player_front)
	{
		printf("Error: Could not load player_front.xpm\n");
		return (0);
	}

	// Load Moka sprite
	game->sprites.moka = mlx_xpm_file_to_image(game->mlx,
		"assets/moka.xpm", &width, &height);
	if (!game->sprites.moka)
	{
		printf("Error: Could not load moka.xpm\n");
		free_sprites(game);
		return (0);
	}

	// Load collectible sprites
	game->sprites.cider = mlx_xpm_file_to_image(game->mlx,
		"assets/cider.xpm", &width, &height);
	game->sprites.croissant = mlx_xpm_file_to_image(game->mlx,
		"assets/croissant.xpm", &width, &height);
	game->sprites.gelato = mlx_xpm_file_to_image(game->mlx,
		"assets/gelato.xpm", &width, &height);
	game->sprites.doner = mlx_xpm_file_to_image(game->mlx,
		"assets/döner.xpm", &width, &height);
	game->sprites.stroopwafel = mlx_xpm_file_to_image(game->mlx,
		"assets/stroopwafel.xpm", &width, &height);

	printf("✅ Sprites loaded successfully!\n");
	return (1);
}

// Free all loaded sprites
void	free_sprites(t_game *game)
{
	if (!game || !game->mlx)
		return;

	if (game->sprites.player_front)
		mlx_destroy_image(game->mlx, game->sprites.player_front);
	if (game->sprites.moka)
		mlx_destroy_image(game->mlx, game->sprites.moka);
	if (game->sprites.cider)
		mlx_destroy_image(game->mlx, game->sprites.cider);
	if (game->sprites.croissant)
		mlx_destroy_image(game->mlx, game->sprites.croissant);
	if (game->sprites.gelato)
		mlx_destroy_image(game->mlx, game->sprites.gelato);
	if (game->sprites.doner)
		mlx_destroy_image(game->mlx, game->sprites.doner);
	if (game->sprites.stroopwafel)
		mlx_destroy_image(game->mlx, game->sprites.stroopwafel);
	if (game->sprites.wall)
		mlx_destroy_image(game->mlx, game->sprites.wall);
	if (game->sprites.floor)
		mlx_destroy_image(game->mlx, game->sprites.floor);
	if (game->sprites.exit)
		mlx_destroy_image(game->mlx, game->sprites.exit);
}

// Helper function for drawing filled rectangles
void	draw_filled_rectangle(t_game *game, int x, int y, int width, int height, int color)
{
	if (!game || !game->mlx || !game->win)
		return;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
		}
	}
}

// Initialize player position
void	init_player(t_game *game)
{
	if (!game)
		return;

	game->player.move_count = 0;
	game->player.sprite_char = 'P';

	// Initialize positions to safe defaults
	game->player.pos.x = 1;
	game->player.pos.y = 1;
	game->player.old_pos = game->player.pos;
	game->moka_pos_x = 1;
	game->moka_pos_y = 1;

	// Find player starting position in current level
	for (int y = 0; y < game->levels[game->current_level].height; y++)
	{
		for (int x = 0; x < game->levels[game->current_level].width; x++)
		{
			if (game->levels[game->current_level].map[y][x] == PLAYER)
			{
				game->player.pos.x = x;
				game->player.pos.y = y;
				game->player.old_pos = game->player.pos;
				// Replace the P in the map with floor so it doesn't render twice
				game->levels[game->current_level].map[y][x] = FLOOR;
			}
			else if (game->levels[game->current_level].map[y][x] == MOKA)
			{
				game->moka_pos_x = x;
				game->moka_pos_y = y;
				// Replace the M in the map with floor so it doesn't render twice
				game->levels[game->current_level].map[y][x] = FLOOR;
			}
		}
	}
}

// Load a specific level
void	load_level(t_game *game, int level_index)
{
	if (level_index >= MAX_CITIES)
		return;

	game->current_level = level_index;
	game->levels[level_index].collected = 0;

	// Find player and Moka positions
	for (int y = 0; y < game->levels[level_index].height; y++)
	{
		for (int x = 0; x < game->levels[level_index].width; x++)
		{
			if (game->levels[level_index].map[y][x] == PLAYER)
			{
				game->player.pos.x = x;
				game->player.pos.y = y;
				game->player.old_pos = game->player.pos;
				// Replace the P in the map with floor so it doesn't render twice
				game->levels[level_index].map[y][x] = FLOOR;
			}
			else if (game->levels[level_index].map[y][x] == MOKA)
			{
				game->moka_pos_x = x;
				game->moka_pos_y = y;
				// Replace the M in the map with floor so it doesn't render twice
				game->levels[level_index].map[y][x] = FLOOR;
			}
		}
	}

	game->state = GAME_PLAYING;
}

// Check if current level is complete
int	check_level_complete(t_game *game)
{
	t_level *current = &game->levels[game->current_level];
	return (current->collected >= current->total_collectibles);
}

// Advance to next level
void	advance_to_next_level(t_game *game)
{
	game->current_level++;

	if (game->current_level >= MAX_CITIES)
	{
		game->state = GAME_WON;
		printf("\n🎉 CONGRATULATIONS! 🎉\n");
		printf("You've completed all cities together!\n");
		printf("From London to Amsterdam - what an amazing journey through our memories! 💕\n");
		return;
	}

	load_level(game, game->current_level);
	print_level_info(game);
}

// Move player
int	move_player(t_game *game, int dx, int dy)
{
	if (!game)
		return (0);

	int new_x = game->player.pos.x + dx;
	int new_y = game->player.pos.y + dy;

	if (!is_valid_move(game, new_x, new_y))
		return (0);

	game->player.old_pos = game->player.pos;
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
	game->player.move_count++;

	// Check for collectibles
	char tile = game->levels[game->current_level].map[new_y][new_x];
	if (tile == COLLECTIBLE)
		collect_item(game, new_x, new_y);
	else if (tile == EXIT && check_level_complete(game))
	{
		game->state = GAME_LEVEL_COMPLETE;
		printf("\n✨ LEVEL COMPLETE! Press SPACE to continue to the next city! ✨\n");
	}

	return (1);
}

// Check if move is valid
int	is_valid_move(t_game *game, int x, int y)
{
	if (!game)
		return (0);

	// Check if current level is valid
	if (game->current_level < 0 || game->current_level >= MAX_CITIES)
		return (0);

	t_level *current = &game->levels[game->current_level];

	// Check if map exists
	if (!current->map)
		return (0);

	if (x < 0 || x >= current->width || y < 0 || y >= current->height)
		return (0);

	// Check if the specific map row exists
	if (!current->map[y])
		return (0);

	char tile = current->map[y][x];
	return (tile != WALL);
}

// Collect item
void	collect_item(t_game *game, int x, int y)
{
	t_level *current = &game->levels[game->current_level];

	current->map[y][x] = FLOOR;  // Remove collectible from map
	current->collected++;

	printf("Collected %s! (%d/%d)\n",
		current->collectible_name,
		current->collected,
		current->total_collectibles);

	if (check_level_complete(game))
	{
		printf("\n🎊 Level Complete! All %s collected in %s! 🎊\n",
			current->collectible_name, current->name);
		printf("Find the exit to continue to the next city!\n");
	}
}

// Update game state
void	update_game(t_game *game)
{
	(void)game;  // Suppress unused parameter warning
	// Game logic updates go here
	// For now, we'll keep it simple
}

// Render the game
void	render_game(t_game *game)
{
	// Clear window with a nice background color
	mlx_clear_window(game->mlx, game->win);

	draw_map(game);
	draw_ui(game);
}

// Draw the map
void	draw_map(t_game *game)
{
	t_level *current = &game->levels[game->current_level];

	for (int y = 0; y < current->height; y++)
	{
		for (int x = 0; x < current->width; x++)
		{
			char tile = current->map[y][x];

			// Override with player position
			if (x == game->player.pos.x && y == game->player.pos.y)
				draw_tile(game, PLAYER, x, y);
			else if (x == game->moka_pos_x && y == game->moka_pos_y)
				draw_tile(game, MOKA, x, y);
			else
				draw_tile(game, tile, x, y);
		}
	}
}

// Draw a single tile (simplified version using rectangles)
void	draw_tile(t_game *game, char tile, int x, int y)
{
	if (!game || !game->mlx || !game->win)
		return;

	// Bounds checking
	if (x < 0 || y < 0 || x >= 15 || y >= 10)
		return;

	int pixel_x = x * TILE_SIZE + 40;  // 40px margin from edge
	int pixel_y = y * TILE_SIZE + 40;
	int color;

	// Additional window bounds check
	if (pixel_x < 0 || pixel_y < 0 || pixel_x >= WIN_WIDTH || pixel_y >= WIN_HEIGHT)
		return;

	switch (tile)
	{
		case WALL:
			color = 0x8B4513;  // Brown walls
			draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			break;
		case FLOOR:
			color = 0xF5F5DC;  // Beige floor
			draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			break;
		case PLAYER:
			// Draw floor first
			color = 0xF5F5DC;
			draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			// Then draw player sprite if available
			if (game->sprites.player_front)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.player_front, pixel_x, pixel_y);
			else
			{
				color = 0xFF1493;  // Fallback pink color
				draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			}
			break;
		case COLLECTIBLE:
			// Draw floor first
			color = 0xF5F5DC;
			draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			// Draw city-specific collectible sprite
			{
				void *collectible_sprite = NULL;
				switch (game->current_level)
				{
					case LONDON:
						collectible_sprite = game->sprites.cider;
						break;
					case PARIS:
						collectible_sprite = game->sprites.croissant;
						break;
					case ROME:
						collectible_sprite = game->sprites.gelato;
						break;
					case BERLIN:
						collectible_sprite = game->sprites.doner;
						break;
					case AMSTERDAM:
						collectible_sprite = game->sprites.stroopwafel;
						break;
				}

				if (collectible_sprite)
					mlx_put_image_to_window(game->mlx, game->win, collectible_sprite, pixel_x, pixel_y);
				else
				{
					// Fallback to colored rectangle if sprite not available
					color = 0xFFD700;  // Gold color
					draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
				}
			}
			break;
		case EXIT:
			color = 0x00FF00;  // Green exit
			draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			break;
		case MOKA:
			// Draw floor first
			color = 0xF5F5DC;
			draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			// Then draw Moka sprite if available
			if (game->sprites.moka)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.moka, pixel_x, pixel_y);
			else
			{
				color = 0xFF4500;  // Fallback orange color
				draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			}
			break;
		default:
			color = 0xF5F5DC;  // Default floor
			draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			break;
	}
}

// Draw UI information
void	draw_ui(t_game *game)
{
	(void)game;  // Suppress unused parameter warning
	// For now, we'll just use printf for game info
	// In a full implementation, you'd use mlx_string_put
}

// Print level information
void	print_level_info(t_game *game)
{
	t_level *current = &game->levels[game->current_level];

	printf("\n=== Welcome to %s! ===\n", current->name);
	printf("🎯 Collect all %d %s to unlock the exit!\n",
		current->total_collectibles, current->collectible_name);
	printf("🐕 Look for Moka somewhere in the city!\n");
	printf("Controls: WASD or Arrow Keys to move, ESC to quit\n");
	printf("Progress: %d/%d %s collected\n\n",
		current->collected, current->total_collectibles, current->collectible_name);
}

// Free game resources
void	free_game(t_game *game)
{
	// Free sprites first
	free_sprites(game);

	for (int level = 0; level < MAX_CITIES; level++)
	{
		if (game->levels[level].map)
		{
			for (int i = 0; i < game->levels[level].height; i++)
			{
				if (game->levels[level].map[i])
					free(game->levels[level].map[i]);
			}
			free(game->levels[level].map);
		}
	}

	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}
