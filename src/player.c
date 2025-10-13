#include "adventure.h"
#include <stdio.h>

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

				// Place Moka to the left of the player (preferred), otherwise right
				if (x - 1 >= 0 &&
					game->levels[game->current_level].map[y][x - 1] != WALL)
				{
					game->moka_pos_x = x - 1;
					game->moka_pos_y = y;
				}
				else if (x + 1 < game->levels[game->current_level].width &&
					game->levels[game->current_level].map[y][x + 1] != WALL)
				{
					game->moka_pos_x = x + 1;
					game->moka_pos_y = y;
				}
				else
				{
					// Fallback: place Moka at the same position as player
					game->moka_pos_x = x;
					game->moka_pos_y = y;
				}

				// Replace the P in the map with floor so it doesn't render twice
				game->levels[game->current_level].map[y][x] = FLOOR;
			}
			else if (game->levels[game->current_level].map[y][x] == MOKA)
			{
				// Replace any existing M in the map with floor (we'll position Moka dynamically now)
				game->levels[game->current_level].map[y][x] = FLOOR;
			}
		}
	}
}

// Move player and handle collisions
int	move_player(t_game *game, int dx, int dy)
{
	if (!game)
		return (0);

	int new_x = game->player.pos.x + dx;
	int new_y = game->player.pos.y + dy;

	if (!is_valid_move(game, new_x, new_y))
		return (0);

	// Update player position
	game->player.old_pos = game->player.pos;
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
	game->player.move_count++;

	// Move Moka to player's old position (following behavior)
	// Check if the old position is valid for Moka
	if (is_valid_move(game, game->player.old_pos.x, game->player.old_pos.y))
	{
		game->moka_pos_x = game->player.old_pos.x;
		game->moka_pos_y = game->player.old_pos.y;
	}
	// If old position is not valid, keep Moka where they are

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

// Check if a move is valid (not into walls, within bounds)
int	is_valid_move(t_game *game, int x, int y)
{
	if (!game)
		return (0);

	t_level *current = &game->levels[game->current_level];

	// Check bounds
	if (x < 0 || x >= current->width || y < 0 || y >= current->height)
		return (0);

	// Check for walls
	char tile = current->map[y][x];
	if (tile == WALL)
		return (0);

	// Check if trying to move to exit without completing level
	if (tile == EXIT && !check_level_complete(game))
	{
		printf("🚪 Complete all objectives before using the exit!\n");
		return (0);
	}

	return (1);
}

// Collect item at given position
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
