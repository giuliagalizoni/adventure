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
		"1000000000000001",
		"1111111111111111",
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
		"1000000C000C0001",
		"1111111111111111",
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
		"100000C000C00001",
		"1111111111111111",
		"111111111111111"
	};

	// Allocate memory for maps and copy data
	for (int level = 0; level < MAX_CITIES; level++)
	{
		game->levels[level].map = malloc(sizeof(char *) * game->levels[level].height);
		if (!game->levels[level].map)
			return (0);

		for (int i = 0; i < game->levels[level].height; i++)
		{
			game->levels[level].map[i] = malloc(sizeof(char) * (game->levels[level].width + 1));
			if (!game->levels[level].map[i])
				return (0);

			// Copy the appropriate map
			if (level == LONDON)
				strcpy(game->levels[level].map[i], london_map[i]);
			else if (level == PARIS)
				strcpy(game->levels[level].map[i], paris_map[i]);
			else if (level == ROME)
				strcpy(game->levels[level].map[i], rome_map[i]);
			else if (level == BERLIN)
				strcpy(game->levels[level].map[i], berlin_map[i]);
			else if (level == AMSTERDAM)
				strcpy(game->levels[level].map[i], amsterdam_map[i]);
		}
	}

	return (1);
}

// Initialize player position
void	init_player(t_game *game)
{
	game->player.move_count = 0;
	game->player.sprite_char = 'P';

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

				// Find Moka's position too
				if (game->levels[game->current_level].map[y][x] == MOKA)
				{
					game->moka_pos_x = x;
					game->moka_pos_y = y;
				}
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
			}
			else if (game->levels[level_index].map[y][x] == MOKA)
			{
				game->moka_pos_x = x;
				game->moka_pos_y = y;
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
	t_level *current = &game->levels[game->current_level];

	if (x < 0 || x >= current->width || y < 0 || y >= current->height)
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
	int pixel_x = x * TILE_SIZE + 40;  // 40px margin from edge
	int pixel_y = y * TILE_SIZE + 40;
	int color;

	switch (tile)
	{
		case WALL:
			color = 0x8B4513;  // Brown walls
			break;
		case FLOOR:
			color = 0xF5F5DC;  // Beige floor
			break;
		case PLAYER:
			color = 0xFF1493;  // Pink for player (you!)
			break;
		case COLLECTIBLE:
			color = 0xFFD700;  // Gold for collectibles
			break;
		case EXIT:
			color = 0x00FF00;  // Green exit
			break;
		case MOKA:
			color = 0xFF4500;  // Orange for Moka (distinguishable from walls!)
			break;
		default:
			color = 0xF5F5DC;  // Default floor
			break;
	}

	// Draw a filled rectangle for each tile
	for (int i = 0; i < TILE_SIZE - 2; i++)
	{
		for (int j = 0; j < TILE_SIZE - 2; j++)
		{
			mlx_pixel_put(game->mlx, game->win, pixel_x + i, pixel_y + j, color);
		}
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
